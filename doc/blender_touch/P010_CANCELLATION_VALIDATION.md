# P010 — Cancelamento e troca de janela

## Objetivo

Verificar que um contato interrompido ao trocar de janela termina com
`TOUCH_CANCEL`, não reaparece por eventos atrasados e não impede novos toques
nem o uso do touchpad.

## Teste no Galaxy Book

No build completo local, aberto com `--factory-startup --debug-events`, o usuário
manteve um dedo na área 3D, usou `Alt+Tab` sem soltar, retirou o dedo, voltou ao
Blender e testou novo toque e clique no cubo com o touchpad. Confirmou que a
janela continuou respondendo.

O registro `C:\btfull\p010-focus-retest.out.log` mostra:

- O contato 2322 começou com `TOUCH_DOWN` e terminou em `TOUCH_CANCEL`, com
  `contacts:0`, durante a troca de janela. Nenhum `MOVE` ou `UP` desse ID apareceu
  depois do cancelamento.
- Os contatos seguintes, 2323 a 2326, começaram e terminaram normalmente com
  `TOUCH_UP` e `contacts:0`.
- No total, houve cinco `TOUCH_DOWN`, 196 `TOUCH_MOVE`, um `TOUCH_CANCEL` e quatro
  `TOUCH_UP`. Cada movimento e encerramento pertenceu a um contato ativo; não
  houve ID duplicado, contagem incorreta ou contato restante no fim.
- Depois dos novos toques, o registro também contém `LEFTMOUSE` pressionado e
  solto pelo touchpad. O arquivo de erros da execução está vazio.

O teste anterior em `touch-retest.out.log`, feito após a correção da P006,
também havia mostrado cancelamento sem eventos atrasados. Esta execução repete
o caso no build que já inclui a ativação da janela por toque da P007.

## Caminho no código

O GHOST cancela o contato associado quando recebe `WM_POINTERCAPTURECHANGED` e
cancela os contatos da janela quando ela é desativada ou ocorre
`WM_DISPLAYCHANGE`. Após remover um contato, ignora `WM_POINTERUPDATE` e
`WM_POINTERUP` atrasados para esse ID até que exista um novo `WM_POINTERDOWN`.
O teste físico acima cobriu a troca de janela; mudança de resolução e rotação
da tela permanecem nos testes de estabilização P030–P034.

**Saída da P010:** cancelamento e retomada após troca de janela validados no
aparelho. Não foi necessário alterar o código nesta etapa.
