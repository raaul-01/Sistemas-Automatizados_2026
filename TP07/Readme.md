# Programação sequencial de CLP: TON, intermitência, CTU e reset

Disciplina: Sistemas Automatizados, Semana 7 (Programação sequencial de CLP)
Simulador: PLC Simulator online (studio.rungs.dev)

## Links dos projetos
- MOTOR_DELAY: https://app.plcsimulator.online/Lg8X0kS9d5p7IINhXe6X
- PISCA: https://app.plcsimulator.online/kasnBtZlZ1BxjtH1EBdm
- Lote com reset (CTU): https://app.plcsimulator.online/VFfhoJ3wkZEUd2DV7OVV

Se um link não abrir, o programa está nas capturas `capturas/ladder_*.png`.

## 1. Exercício obrigatório: atraso de partida (MOTOR_DELAY)

START habilita um TON de 3 s. A saída MOTOR_DELAY liga quando o timer termina.
STOP_OK=0 ou EMG_OK=0 interrompem a temporização e removem a saída.

### Tags
| Tag | Tipo | Função | Convenção |
|---|---|---|---|
| START | Bool, entrada | Botão de partida | 1 = pressionado |
| STOP_OK | Bool, entrada | Condição de parada | 1 = normal, 0 = parada acionada |
| EMG_OK | Bool, entrada | Emergência | 1 = normal, 0 = emergência acionada |
| MOTOR_DELAY | Bool, saída | Motor com atraso | 1 = ligado |
| T1 | Timer TON | Atraso de partida | PT = 3000 ms |

### Lógica (linha a linha)
- Linha 1: EMG_OK, STOP_OK e START em série (AND) alimentam o IN do TON T1.
  Com as três em 1, o ET sobe de 0 até 3000 ms.
- Linha 2: o contato T1.Q aciona a bobina MOTOR_DELAY. A saída liga só quando o timer termina.
- Falha: se EMG_OK ou STOP_OK forem a 0, a linha 1 perde continuidade, o timer
  zera (ET=0, Q=0) e a saída desliga.

### Decisões e prioridades
- STOP_OK e EMG_OK usam lógica positiva de segurança (1 = normal). Um fio rompido
  leva o sinal a 0 e o sistema para.
- Segurança tem prioridade sobre o comando: STOP_OK=0 ou EMG_OK=0 anulam START.
  Mesmo com START=1, o timer não conta e a saída não liga.
- START é mantido, sem selo. Soltar START antes dos 3 s cancela a partida.
  Ao liberar a falha, a partida só ocorre com um novo START.
- A saída é comandada somente pelo bit Q do timer.

Capturas: `T01` a `T05` na pasta `capturas/`. Testes: T01 a T05 em `casos_teste.csv`.

## 2. Extensão 1: sinal intermitente (PISCA)

Lâmpada 1 s ligada e 1 s desligada. Dois TON (T_OFF e T_ON, PT = 1000 ms) e a
memória PISCA, que muda por bobinas S (comandada por T_OFF.Q) e R (comandada por
T_ON.Q). LAMPADA acompanha PISCA.

- Linha 1: contato negado de PISCA habilita T_OFF.
- Linha 2: contato de PISCA habilita T_ON.
- Linha 3: T_OFF.Q aciona a bobina S de PISCA.
- Linha 4: T_ON.Q aciona a bobina R de PISCA.
- Linha 5: contato de PISCA aciona a bobina LAMPADA.

Capturas: `ladder_pisca.png`, `E1_fase_ligada.png`, `E1_fase_desligada.png`.
Registro de 6 s: teste P01 em `casos_teste.csv`.

### Como evitei múltiplas inversões
PISCA só muda pelas bobinas S e R. Cada fase é temporizada por um TON diferente,
habilitado por PISCA (negado em T_OFF, normal em T_ON). Quando um timer termina,
altera PISCA uma única vez, e essa mudança desabilita o próprio timer na varredura
seguinte (ET e Q zeram). A inversão não se repete até a outra fase completar 1 s.

Observação: para capturar a fase desligada, o PT do T_OFF foi alterado
temporariamente para 5000 ms e depois restaurado para 1000 ms. O programa final
usa 1000 ms nos dois timers.

## 3. Extensão 2: lote completo (CTU)

Contador CTU `CONT` com PV = 5. O contato S_PECA aciona a entrada CU e `CONT.QU`
aciona LOTE_OK. (No simulador a variável aparece como S_PEÇA.)

- Uma contagem por peça: o CTU conta só a borda de subida (0 para 1).
- Com S_PECA mantido em 1 por cerca de 5 s, o CV permaneceu em 1.
- Em CV = 5, QU e LOTE_OK vão a 1.
- O CTU deste simulador continua contando acima do PV (foi observado CV = 7),
  por isso o reset é necessário.

Capturas: `E2_meio_cv4.png`, `E2_lote_completo.png`, `E2_sensor_mantido.png`.
Testes: C01 e C02 em `casos_teste.csv`.

## 4. Extensão 3: zeragem controlada (RESET_LOTE)

A variável RESET_LOTE aciona, numa terceira linha, a bobina `CONT.R`. A entrada R
do bloco aceita apenas um valor fixo (true ou falso), por isso o reset foi feito
por bobina na variável CONT.R.

Capturas: `ladder_lote_reset.png`, `E3_antes_reset.png`,
`E3_reset_lote_completo.png`, `E3_reset_e_contagem.png`.
Testes: R1 a R4 em `casos_teste.csv`.

### Prioridade adotada
O reset tem prioridade sobre a contagem. Com RESET_LOTE=1 mantido, os pulsos em
S_PECA não alteraram o CV, que permaneceu em 0 (teste R4). Com o reset liberado,
a contagem volta a funcionar normalmente.

## Como testar
1. Iniciar a simulação com os valores iniciais de cada programa
   (MOTOR_DELAY: START=0, STOP_OK=1, EMG_OK=1).
2. Executar os casos de `casos_teste.csv`, alterando as variáveis na tabela do simulador.
3. Observar IN, ET, Q, CV, QU e as saídas.

## Escopo
Esta entrega cobre o exercício obrigatório (TON) e as extensões 1 a 3
(intermitência, CTU e reset). A extensão 4 (GRAFCET para Ladder) não foi incluída.
