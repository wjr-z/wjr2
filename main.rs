use std::fs::File;
use std::io::{BufRead, BufReader};
use std::sync::{Arc, Condvar, Mutex};
use std::time::Instant;
use wasmtime::*; 
use wasmtime_wasi::WasiCtx;
use wasmtime_wasi::sync::WasiCtxBuilder;

#[macro_use]
extern crate lazy_static;

fn read(str: &mut String, buffer: &mut BufReader<File>) {
    let _ = buffer.read_line(str);
}

lazy_static! {
    static ref RUNNER : tokio::runtime::Runtime =
        tokio::runtime::Builder::new_multi_thread().build().unwrap();
}

fn main() {
    let mut str = String::new();
    let file = File::open("input.txt").expect("Error in reading file");
    let mut buffer = BufReader::new(file);

    read(&mut str, &mut buffer);

    let n = str.trim().parse::<i64>().unwrap();

    let mutex = Arc::new(Mutex::<i32>::new(0));
    let cv = Arc::new(Condvar::new());

    // let mut config = Config::default();
    // config
    // .native_unwind_info(true)
    // .wasm_backtrace(true)
    //     .async_support(true)
    //     .epoch_interruption(true)
    //     .cache_config_load_default()
    //     .unwrap();
    // let engine = Engine::new(&config).unwrap();

    // let mut linker = Linker::new(&engine);
    // let _ = wasmtime_wasi::add_to_linker(&mut linker, |cx| cx).unwrap();
    // let wasi_ctx = WasiCtxBuilder::new().inherit_stdio().build();

    // let engine2 = engine.clone();

    // std::thread::spawn(move || {
    //     loop {
    //         std::thread::sleep(std::time::Duration::from_millis(1));
    //         engine2.increment_epoch();
    //     }
    // });

    let push =
        move |engine: Engine, linker: Linker<WasiCtx>, wasi_ctx : WasiCtx, mutex: Arc<Mutex<i32>>, cv: Arc<Condvar>| {
            // let mut store = Store::new(&engine, wasi_ctx );
            // store.set_epoch_deadline(1);
            // store.epoch_deadline_async_yield_and_update(1);
            RUNNER.spawn(async move {
                // let module = unsafe{Module::from_trusted_file(&engine, "test.wat")}.unwrap();
                // let instance = linker.instantiate_async(&mut store, &module).await.unwrap();
                // let func = instance
                //     .get_typed_func::<(), ()>(&mut store, "foo")
                //     .unwrap();

                // let _ = func.call_async(&mut store, ()).await;

                tokio::time::sleep(std::time::Duration::from_millis(1)).await;

                let mut lock = mutex.lock().unwrap();
                *lock -= 1;
                if *lock == 0 {
                    cv.notify_one();
                }
            });
        };

    let start = Instant::now();

    for _ in 0..n {
        push(engine.clone(), linker.clone(), wasi_ctx.clone(), mutex.clone(), cv.clone());
    }

    {
        let mut lock = mutex.lock().unwrap();
        while *lock != 0 {
            lock = cv.wait(lock).unwrap();
        }
    }

    println!("all done at {} ms", start.elapsed().as_millis());
}
