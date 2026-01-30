use std::{env, path};

use rustc_codegen_nvvm::CudaBuilder;

fn main() {
    println!("cargo::rerun-if-changed=build.rs");
    println!("cargo::rerun-if-changed=kernels");

    let out_dir = path::PathBuf::from(env::var("OUT_DIR").unwrap());    
    let maifest_dir = path::PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap());

    // Compile the 'kernels' crate to '$OUT_DIR/kernels.ptx'
    CudaBuilder::new(manifest_dir.join("kernels"))
        .copy_to(out_dir.join("kernels"))
        .build()
        .unwrap();
}
