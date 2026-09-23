# P009 — Contatos simultâneos

## Objetivo

Confirmar no Galaxy Book que dois dedos na tela mantêm identificadores distintos
e ciclos independentes de início, movimento e fim no fluxo Windows → GHOST →
Window Manager.

## Resultado

O registro local `C:\btfull\p007-focus-first-touch.out.log`, coletado com o build
completo e `--debug-events`, contém 23 `TOUCH_DOWN`, 661 `TOUCH_MOVE` e 23
`TOUCH_UP`. Três sequências tiveram dois dedos ativos ao mesmo tempo:

| IDs | Movimentos durante a sobreposição |
| --- | --- |
| 2219 e 2220 | 39 de cada dedo |
| 2230 e 2231 | 34 de cada dedo |
| 2241 e 2242 | 121 de cada dedo |

Em todas as sequências, a contagem passou de um para dois contatos ao entrar o
segundo dedo e voltou a um e depois zero nas retiradas. No registro inteiro,
nenhum `MOVE` ou `UP` apareceu sem um `DOWN` ativo; não houve `DOWN` duplicado,
contagem divergente ou contato ainda ativo no fim.

O registro anterior `touch-smoke.out.log` foi coletado antes da correção do
cancelamento e contém movimentos após um contato cancelado. Ele não serve como
critério de aprovação da P009. O registro posterior acima confirma o fluxo de
dois dedos com a correção aplicada. A validação específica do cancelamento e da
troca de janela pertence à P010.

## Caminho no código

O GHOST guarda cada contato pelo ID recebido do Windows e calcula a quantidade
ativa por janela. O Window Manager preserva ID, contagem, posição, pressão e
indicador de contato primário no evento entregue ao Blender. O registro físico
confirma que os dois IDs avançam independentemente por esse caminho.

**Saída da P009:** dois contatos simultâneos validados no aparelho. Não foi
necessário alterar o código. O teste prolongado com mais dedos permanece na
etapa de estabilização P030–P034.
