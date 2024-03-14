# circle_fit
Bilioteca que fita pontos em um plano cartesiano com equação de circulo

Autor: Alison de Oliveira Tristão
email: AlisonTristao@hotmail.com

Usamos a equação do circulo:

(x + x0)² + (y + y0)² = R²

            ||

            \/

2x0 x + 2y0 y + (x0² + y0² -R²) = x²+y²

a x   + b y   + c               = x²+y²

logo, para N pontos:

[x1 y1 1] * [a] = [x1²+y1²]

    ...     [b]      ...

[xn yn 1]   [c]   [xn²+yn²]

solucionando esses sistema super determinado, 
achamos o raio e o centro deslocado