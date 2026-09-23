# P008 — Separação entre toque, S Pen e mouse

## Objetivo

Confirmar que o Windows e o Blender preservam a origem da entrada: dedo vira
evento de toque, S Pen continua usando a rota de tablet e mouse ou touchpad
continuam enviando eventos de mouse.

## Resultado no Galaxy Book

- O registro de toque contém 18 `TOUCH_DOWN`, 2.167 `TOUCH_MOVE`, 18 `TOUCH_UP`
  e um `TOUCH_CANCEL`, com até três contatos simultâneos.
- Nenhum dos 46 eventos de botão do mouse registrados coincidiu com as
  coordenadas dos eventos de toque. A tela não gerou cliques de mouse duplicados.
- Com Windows Ink, o Blender classificou 12 amostras da S Pen como dados de
  tablet e registrou pressão e inclinação. O teste anterior do touchpad gerou
  eventos de mouse classificados separadamente.
- O usuário confirmou que touchpad, S Pen, pressão e borracha funcionaram sem
  clique duplicado. Um teste sem o monitor modal também confirmou que touchpad e
  S Pen continuaram respondendo normalmente.

## Caminho no código

- `PT_TOUCH` vira `GHOST_EventTouch`; a mensagem de mouse compatível que o
  Windows promove a partir desse toque é descartada.
- `PT_PEN` usa a rota Windows Ink de cursor e botões quando Windows Ink está
  selecionado. Quando Wintab é selecionado, a rota existente do Wintab continua
  responsável pela caneta.
- Mouse e touchpad mantêm a rota habitual de cursor e botões.

**Saída da P008:** a separação de origem entre toque, caneta e mouse passou no
aparelho. Não foi necessário alterar o código nesta etapa. Rejeição de palma e
uso simultâneo de palma e caneta continuam previstos para P025.
