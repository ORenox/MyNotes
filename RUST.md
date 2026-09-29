#rustAnalizer
`rust-analyzer` te da autocompletado inteligente, te muestra los errores de tu código en tiempo real antes de compilar y te explica visualmente qué tipos de datos estás usando, algo vital al aprender Rust.

#IDEs 

- **RustRover**: Es un IDE dedicado exclusivamente para Rust. Es extremadamente potente, rápido y tiene soporte nativo avanzado para refactorización de código. Es gratuito para uso no comercial (estudiantes, proyectos personales o código abierto). 

#ProbarEntorno 
```bash
cargo new mi_primer_proyecto 
cd mi_primer_proyecto
```

Abre esa carpeta en tu IDE. Verás un archivo llamado `src/main.rs` con un "Hello, world!". Para ejecutarlo, simplemente escribe en la terminal de tu IDE:
```
cargo run
```


## Ejemplo de "Inferencia de Tipos" en pantalla

Rust es un lenguaje fuertemente tipado, pero te permite omitir los tipos de datos porque el compilador los adivina. `rust-analyzer` en VS Code te mostrará el tipo de dato en texto gris semi-transparente (_Inlay Hints_).


```rust
fn main() {
    let mut velocidad = 10; // No le dices qué es
    let mensaje = "Robot activo";
}
```


```rust
fn main() {
    let mut velocidad: i32 = 10; // VS Code te añade ": i32" visualmente
    let mensaje: &str = "Robot activo"; // VS Code te añade ": &str" visualmente
}
```