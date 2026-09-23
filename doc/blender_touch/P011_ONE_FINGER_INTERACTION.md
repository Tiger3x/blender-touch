# P011 — Interação com um dedo

## Comportamento definido

Um dedo pode interagir com a área de conteúdo do Blender, incluindo editores,
viewport, cabeçalhos, painéis, menus e janelas de diálogo. A moldura e os
controles da janela do Windows continuam sob responsabilidade do sistema.

- `TOUCHDOWN` move o ponteiro para o contato e gera um pressionamento do botão
  esquerdo. Assim, um toque curto aciona um único controle da interface.
- `TOUCHMOVE` atualiza a posição enquanto o botão permanece pressionado; isso
  entrega arrastos e operações modais ao caminho de mouse já usado pelo Blender.
- `TOUCHUP` atualiza a posição final e solta o botão esquerdo.
- `TOUCHCANCEL` solta o botão sem enviar um movimento final, evitando uma
  operação de mouse presa quando o contato é interrompido.
- Se outro dedo entrar, o botão esquerdo é solto e a sequência volta a ser
  somente eventos brutos de toque até que todos os dedos saiam.

Os eventos brutos `TOUCHDOWN`, `TOUCHMOVE`, `TOUCHUP` e `TOUCHCANCEL` continuam
na fila para os futuros gestos. O touchpad e a S Pen mantêm seus próprios
caminhos de entrada; o ponteiro de toque vira mouse apenas por estes eventos
explícitos do Window Manager.

## Implementação e build

O Window Manager guarda por janela o ID do contato que está controlando o botão
esquerdo e se uma sequência multitouch precisa ficar bloqueada até terminar.
Os eventos sintéticos passam pelo tratamento normal de movimento e clique do
Blender. A tradução cobre a área cliente da janela e não altera os eventos
físicos de mouse ou tablet.

Os builds completo e Lite para Windows terminaram com sucesso usando Ninja. Os
executáveis portáteis atualizados estão em `C:\btfull\portable\blender.exe` e
`C:\btlite\portable\blender.exe`.

## Validação física (P012)

No Galaxy Book, o usuário confirmou que o toque seleciona, que o teclado
continua respondendo e que a seleção por caixa acompanha o dedo durante o
arrasto e termina ao soltar. `G` também foi reconhecido no início do teste.
Touchpad e S Pen já haviam respondido normalmente nos testes de regressão, sem
clique duplicado relatado.

O usuário tentou mover o cubo com `G` e arrastando o dedo, mas não conseguiu.
Isso não valida o arrasto definido nesta etapa: a P011 emula o botão esquerdo
do mouse, então um arrasto comum na viewport deve produzir a operação padrão do
Blender (por exemplo, seleção por caixa quando começa em espaço vazio). A P011
não implementa um gesto independente de “pegar e mover” diretamente o objeto.
O arrasto padrão passou: a seleção acompanhou o dedo e terminou ao soltá-lo, sem
deixar a interface presa.

Durante o mesmo teste, o usuário iniciou `G` e depois encostou o dedo para
mover o objeto. O movimento parou no contato. Isso é explicado pelo contrato
atual: o `TOUCHDOWN` gera `LEFTMOUSE/KM_PRESS`, e o mapa padrão do Blender usa
esse pressionamento para confirmar a transformação modal. Portanto, a P011
passou na emulação de clique/arrasto padrão, mas ainda não permite continuar um
`G` com o dedo depois de iniciar a operação pelo teclado. Esse caso deve ser
resolvido na próxima etapa de interação por toque.

**Saída da P011:** implementação e builds concluídos. A validação física está
concluída; P012 fechada.
