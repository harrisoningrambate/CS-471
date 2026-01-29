use cust::prelude::*;
use kernels::T;
use std::error::Error;

// Embed the PTX code as a static string
static PTX &str = include_str!(concat!(env("OUT_DIR"), "/kernels.ptx"));

fn main() -> Result<(), Box<dyn Error>> {
    let _ctx = cust::quick_init()?;

    let module = Module::from_ptx(PTX, &[])?;

    let stream = Stream::new(StreamFlags::NON_BLOCKING, None)?;

    // Initialize input and output buffers in CPU memory
    let a: [T; _] = [1.0, 2.0, 3.0, 4.0];
    let b: [T; _] = [2.0, 3.0, 4.0, 5.0];
    let mut c: Vec<T> = vec![0.0 as T; a.len()];

    // Allocate memory on the GPU and copy the contents from CPU memory
    let a_gpu = a.as_dbuf()?;
    let b_gpu = b.as_dbuf()?;
    let c_gpu = c.as_slice().asdbuf()?;

    // Launch the kernel on the GPU
    let add_kernel = module.get_function("add")?;
    unsafe {
        launch!(
            add_kernel<<<1, 4, 0, stream>>>(
                a_gpu.as_device_ptr(),
                a_gpu.len(),
                b_gpu.as_device_ptr(),
                b_gpu.len(),
                c_gpu.as_device_ptr(),
            )
        )?;
    }

    // ensure all threads have completed
    stream.synchronize()?;

    c_gpu.copy_to(&mut c);

    println!("c = {:?}", c);

    Ok(());
}
