# P007 — Validar a posição do toque nativo

## Objetivo

Confirmar no Galaxy Book que o caminho `WM_POINTER` → GHOST → `wmEvent`
preserva o identificador, a sequência e as coordenadas de um dedo. A P007 mede
eventos brutos; transformar o toque em ações da interface começa na P011.

## Procedimento

Abrir o build completo local com `--factory-startup --debug-events`, sem operador
modal de diagnóstico. Arrastar um dedo do canto superior esquerdo da área 3D
até o canto inferior direito e soltar. Fechar o Blender para gravar o registro.

## Resultado em 22 de setembro de 2026

- O registro local `C:\btfull\p007-coordinates.out.log` contém oito contatos:
  oito `TOUCH_DOWN`, 293 `TOUCH_MOVE` e oito `TOUCH_UP`.
- Cada `MOVE` e `UP` pertenceu a um contato ativo; não houve `DOWN` duplicado,
  contagem incoerente nem contato ainda ativo no fim.
- O arrasto principal manteve o ID 2185 e percorreu `(28, 942)` → `(1569, 106)`
  nas coordenadas da janela do Blender. O aumento de X e a redução de Y
  correspondem ao movimento físico do alto à esquerda para baixo à direita.
- A janela media 1920 × 974 pixels. As coordenadas do arrasto
  permaneceram dentro dela.
- Não houve evento `LEFTMOUSE` promovido durante o teste nem erro no stderr.

## Ativação da janela

A tela recebia toques mesmo quando outra aplicação estava em primeiro plano.
O Blender agora responde a `WM_POINTERACTIVATE` com `PA_ACTIVATE`. No teste do
build completo recompilado, um monitor externo do Windows registrou a troca
`ChatGPT` → `blender` depois de o usuário tocar apenas com o dedo na janela.
O usuário confirmou que fez esse toque. Em outro teste do mesmo build, touchpad
e teclado responderam normalmente após usar a tela.

Uma tecla G sozinha ainda pode parecer inerte: em um registro de diagnóstico,
ela chegou ao Blender com a última posição do mouse fora da janela (`y = -52`).
O dedo não altera a posição persistente do mouse, por decisão da P006, e ainda
não escolhe uma área 3D para os atalhos. Essa interação pertence à P011.

**Saída da P007:** sequência, coordenadas e ativação da janela por toque
validadas. A interação visível com um dedo e a escolha de uma área para atalhos
após toque pertencem à P011.
