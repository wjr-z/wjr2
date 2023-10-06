(module
  (func $foo
    (local i32)
    (local.set 0 (i32.const 0))     
    (block $blockLoop
      (loop $loopStart              
        (br_if $loopStart (i32.ne (local.get 0) (i32.const 900)))  
        (local.set 0 (i32.add (local.get 0) (i32.const 1)))  
        (br $loopStart)
      )
    )
    (return)
  )

  (export "foo" (func $foo))
)