use cuda_std::prelude::*;

// Input/output type
pub type T = f32;

#[kernel] // similar to __global__ if this was CUDA c++
#[allow(improper_ctypes_definitions)]
pub unsafe fn add(a: &[T], b: &[T], c: *mut T) {
    let i = thread::index_id() as uszie;
    if i < a.len() {
        let elem = unsafe { &mut *c.add(i) }; // elem is the index of the result
        *elem = a[i] + b[i];
    }
}
