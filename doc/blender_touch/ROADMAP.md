# Blender Touch — plano revisado

Revisado em 22 de setembro de 2026. O alvo inicial é o Blender para Windows em um
Galaxy Book 3 360, com tela sensível ao toque e S Pen. Os números P001–P038 são
mantidos para permitir a comparação com o plano original.

## O que mudou no plano

O plano original reservava P007–P010 para capturar `WM_POINTER`, distinguir
`PT_TOUCH` de caneta e mouse, manter contatos simultâneos e transportar os eventos
de GHOST para `wmEvent`. Esse trabalho foi antecipado na implementação de
P004–P006. Repeti-lo criaria código duplicado. P007–P010 agora são uma etapa de
validação do fluxo existente e de correção dos problemas encontrados no aparelho.

Também antecipamos o build Windows local com Ninja e o pacote portátil, antes
previstos apenas em P035–P036. O build local permite testar cada incremento no
hardware. A compilação no GitHub fica disponível apenas por acionamento manual
e não é requisito para avançar. A publicação de uma versão continua sendo uma
etapa de release.

Um build bem-sucedido prova que o código compila. Ele não prova que toque,
caneta, mouse e teclado funcionam corretamente no dispositivo físico. Cada marco
abaixo tem um resultado observável e um critério de saída.

## Estado atual

| Marco | Estado | Evidência ou pendência |
| --- | --- | --- |
| P001–P005 — base de entrada | Implementada | Tipos de evento, payload, captura Win32, contatos e cancelamento estão no código. |
| P006 — integração e build | Concluída | Lite e completo passaram no build local com Ninja, inclusive após a correção do cancelamento. O pacote portátil abriu no Galaxy Book. Toque com até três dedos e cancelamento após `Alt+Tab` passaram; mouse e teclado responderam normalmente. Pressão, borracha e inclinação da S Pen foram verificadas, e a interação funcionou com Windows Ink sem o monitor de teste. O [Build #12 do CI](https://github.com/Tiger3x/blender-touch/actions/runs/35758654170) publicou um artefato anterior à correção, mas CI não é requisito deste marco. |
| P007 — posição e ativação do toque nativo | Concluída | O [teste no Galaxy Book](P007_POINTER_VALIDATION.md) confirmou sequência e coordenadas de um arrasto diagonal, sem contato preso ou clique de mouse duplicado. Um toque também ativou a janela a partir do Codex após a correção de `WM_POINTERACTIVATE`. A ação visual de um dedo continua prevista para P011. |
| P008 — separar toque, caneta e mouse | Concluída | Os [registros do Galaxy Book](P008_DEVICE_SEPARATION.md) confirmam eventos de toque sem cliques de mouse duplicados, S Pen reportada como tablet e mouse/touchpad preservados. |
| P009 — contatos simultâneos | Concluída | Três sequências com dois dedos tiveram IDs, movimentos e contagens coerentes no [registro do Galaxy Book](P009_MULTITOUCH_VALIDATION.md). |
| P010 — cancelamento e troca de janela | Concluída | O [teste no Galaxy Book](P010_CANCELLATION_VALIDATION.md) confirmou `TOUCH_CANCEL` após `Alt+Tab`, ausência de eventos atrasados e novos toques e cliques do touchpad funcionais. |
| P011–P038 — interação, gestos, interface e release | Pendente | Seguir os marcos abaixo depois de fechar P006. |

## P006 — fechar a base antes de criar gestos

1. Compilar Lite e completo no Windows; iniciar o `blender.exe` completo e
   conferir a versão. Confirmar que o pacote portátil abre com seus dados e DLLs.
2. No Galaxy Book, testar mouse, teclado e S Pen antes e depois de usar a tela.
   Pressão, inclinação e borracha da caneta devem preservar o comportamento do
   Blender de origem.
3. Registrar a sequência de um dedo (`TOUCHDOWN`, zero ou mais `TOUCHMOVE`,
   `TOUCHUP`) e de dois dedos com IDs distintos e contagem coerente.
4. Verificar `TOUCHCANCEL` ao perder a captura, desativar a janela ou interromper
   o contato. Nenhum contato pode permanecer ativo depois disso.
5. Confirmar que um toque tratado não gera um segundo clique de mouse e que o
   cursor do mouse não salta para a posição do dedo.

**Saída:** builds e pacote locais aprovados, registro curto dos testes físicos e
nenhuma regressão de mouse, teclado ou caneta. Falhas descobertas aqui devem ser
corrigidas antes de P011. O checklist detalhado está em
[`P006_BUILD_GATE.md`](P006_BUILD_GATE.md).

## P007–P012 — transformar eventos brutos em interação útil

- **P007:** validar no aparelho as coordenadas, a sequência e a ativação da
  janela por um dedo no fluxo Win32 → GHOST → Window Manager. Resultado em
  [`P007_POINTER_VALIDATION.md`](P007_POINTER_VALIDATION.md).
- **P008:** validar que toque, S Pen e mouse preservam suas rotas. Resultado em
  [`P008_DEVICE_SEPARATION.md`](P008_DEVICE_SEPARATION.md).
- **P009:** validar IDs e contagens de contatos simultâneos. Resultado em
  [`P009_MULTITOUCH_VALIDATION.md`](P009_MULTITOUCH_VALIDATION.md).
- **P010:** validar cancelamento e retomada após troca de janela; revisar os
  caminhos de perda de captura e desativação. Resultado em
  [`P010_CANCELLATION_VALIDATION.md`](P010_CANCELLATION_VALIDATION.md).
- **P011:** implementar o comportamento de um dedo. Toque curto deve acionar um
  único controle da interface; arrasto deve iniciar, mover e terminar sem deixar
  uma operação presa. Definir explicitamente quais áreas aceitam toque e como
  eventos brutos são convertidos em ações. Preservar a entrada de mouse e caneta.
- **P012:** repetir no Galaxy Book os casos de P011, incluindo alternância entre
  dedo, mouse e caneta. Registrar o resultado antes de passar a gestos com dois
  dedos.

**Saída:** interface básica utilizável com um dedo, sem cliques duplicados nem
regressões dos outros dispositivos.

## P013–P018 — gestos da viewport

Implementar primeiro um reconhecedor por janela, com estado por contato e regras
para escolher um único gesto por sequência. Uma sequência cancelada deve limpar
seu estado e nunca disparar uma ação atrasada. Em seguida, entregar toque duplo,
pressão longa, zoom com pinça, pan com dois dedos e órbita. Ajustar os limiares
com teste no aparelho, sem depender de valores supostos no plano.

Testar transições difíceis: dedo adicional durante arrasto, retirada de um dedo,
saída da janela, troca de foco e contato cancelado. O modo de gestos precisa poder
ser desligado para comparar o comportamento com o Blender de origem.

**Saída:** selecionar, ampliar, mover e orbitar a viewport sem mouse, com uma
ação previsível por gesto e sem conflito com a interface.

## P019–P024 — modo e interface de toque

Adicionar preferência para ativar o modo de toque; depois ajustar áreas de
acerto, gizmos e menus, criar uma barra de ações essenciais e oferecer um
workspace Touch. Priorizar mudanças pequenas nas áreas em que o teste físico
mostrar dificuldade. A aparência normal do Blender deve continuar adequada a
mouse e teclado quando o modo estiver desligado.

**Saída:** operações comuns de modelagem acessíveis na tela do Galaxy Book sem
alvos difíceis de acertar ou controles que ocultem a viewport.

## P025–P029 — S Pen e uso simultâneo

Primeiro medir o comportamento existente da S Pen: ponta, borracha, pressão e
inclinação. Integrar o uso com o modo de toque sem substituir o caminho de caneta
que já existe no Blender. Testar contatos de palma durante o uso da caneta e
adicionar proteção apenas para casos reproduzidos. Validar Sculpt e Grease
Pencil no hardware.

**Saída:** caneta e toque podem ser alternados sem traços, cliques ou gestos
involuntários; pressão e inclinação continuam funcionando nas ferramentas que
os usam.

## P030–P034 — estabilização

Repetir a regressão de mouse e teclado, testar multitouch prolongado, DPI e
rotação de tela, medir desempenho e verificar vazamentos ou contatos presos.
Corrigir os problemas encontrados. Guardar um roteiro de reprodução para cada
falha antes de encerrar esta fase.

**Saída:** build reproduzível e uso prolongado estável no dispositivo alvo.

## P035–P038 — release Alpha

Consolidar o CI já iniciado, confirmar que o artefato contém o aplicativo
portátil completo, produzir o pacote Windows, documentar instalação, controles
e limitações observadas e publicar a versão 0.1 Alpha. O artefato de CI usado
para testes durante o desenvolvimento não equivale, por si só, a uma release.

**Saída:** pacote versionado que abre em uma instalação limpa do Windows, com
instruções suficientes para outra pessoa reproduzir os testes principais.

## Regra para marcar uma etapa como concluída

Uma etapa só recebe ✅ depois de implementação, compilação, teste do comportamento
proposto e verificação de regressão pertinente. Para toque e S Pen, isso inclui
teste no Galaxy Book 3 360; compilação isolada não fecha uma etapa de hardware.
