// ================================
// TypeScript Error Test File
// ================================

// ------------------------
// 1. Faltando identificador
let: number = 10;

// ------------------------
// 2. Faltando tipo
let a:  = 10;

// ------------------------
// 3. Faltando expressão
let a: number = ;

// ------------------------
// 4. Faltando '='
let a: number 10;

// ------------------------
// 5. Tipo inválido
let a: Numb3r = 10;

// ------------------------
// 6. Identificador inválido (começa com número)
let 1a: number = 10;

// ------------------------
// 7. Identificador com caracteres ilegais
let a$: number = 10;

// ------------------------
// 8. Identificador é keyword reservada
let if: number = 10;

// ------------------------
// 9. Múltiplos erros combinados
let: = ;

// ------------------------
// 10. Espaço extra entre ':' e '='
let b: number = 20;

// ------------------------
// 11. Expressão inválida
let c: number = * 10;

// ------------------------
// 12. Expressão complexa inválida
let d: number = 1 + * 2;

// ------------------------
// 13. Token inválido após tipo
let e: number @10;

// ------------------------
// 14. Fim de arquivo inesperado
let f: number =

  // ------------------------
  // 15. Identificador duplicado (erro semântico)
  let a: number = 5;

// ------------------------
// 16. Todos os erros combinados
let: = * $;

// ------------------------
// 17. Falta tipo e expressão
let g: = ;

// ------------------------
// 18. Falta identificador e expressão
let: = 10;

// ------------------------
// 19. Falta '=' mas há valor
let h: number 42;

// ------------------------
// 20. Tipo válido mas expressão inválida
let i: number = +* 10;
