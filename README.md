# circle_fit

Bilioteca que fita pontos em um plano cartesiano com equação de circulo

**Author:** Alison de Oliveira Tristão  
**Email:** AlisonTristao@hotmail.com  

Usamos a equação do circulo:

(x + x0)² + (y + y0)² = R²

2x0 x + 2y0 y + (x0² + y0² - R²) = x² + y²

a x   + b y   + c               = x² + y²

Então, formamos um sistema Ax = b

[x, y, 1] * [a, b, c]^t = [x²+y²] 

No qual, para mais que 3 pontos, temos um sistema superdeterminado.
