# Exercício obrigatório: atraso de partida (MOTOR_DELAY)

Disciplina: Sistemas Automatizados, Semana 7 (Programação sequencial de CLP)

## Objetivo
Implementar em Ladder um atraso de partida. START habilita um TON de 3 s e a saída
MOTOR_DELAY liga quando o timer termina. STOP_OK=0 ou EMG_OK=0 interrompem a
temporização e removem a saída.

## Link do projeto
https://app.plcsimulator.online/Lg8X0kS9d5p7IINhXe6X

## Tags
| Tag | Tipo | Função | Convenção |
|---|---|---|---|
| START | Bool, entrada | Botão de partida | 1 = pressionado |
| STOP_OK | Bool, entrada | Condição de parada | 1 = normal, 0 = parada acionada |
| EMG_OK | Bool, entrada | Emergência | 1 = normal, 0 = emergência acionada |
| MOTOR_DELAY | Bool, saída | Motor com atraso | 1 = ligado |
| T1 | Timer TON | Atraso de partida | PT = 3000 ms |

## Lógica
| Linha | Lógica | Resultado |
|---|---|---|
| 1 | EMG_OK AND STOP_OK AND START habilita o TON T1 | ET aumenta enquanto a condição permanece em 1 |
| 2 | T1.Q comanda MOTOR_DELAY | A saída liga após 3 s |
| 3 (efeito) | NOT EMG_OK ou NOT STOP_OK remove a continuidade da linha 1 | Timer e saída voltam ao estado seguro |

A linha 3 não é um rung separado: é o efeito de abrir qualquer contato da linha 1.

## Decisões de projeto
- STOP_OK e EMG_OK usam lógica positiva de segurança. O valor 1 é a condição normal,
  então os contatos são normalmente abertos. Um fio rompido leva o sinal a 0 e o
  sistema para.
- START é mantido, sem selo. Soltar START antes dos 3 s cancela a partida e zera o timer.
- A saída é comandada somente pelo bit Q do timer.

## Como testar
1. Iniciar a simulação com START=0, STOP_OK=1 e EMG_OK=1.
2. Executar os casos T01 a T05 de `casos_teste.csv`, alterando os valores na tabela de variáveis.
3. Observar IN, ET, Q e MOTOR_DELAY.

## Resultados
Todos os casos passaram. Os valores obtidos estão em `casos_teste.csv`.

| Teste | Captura |
|---|---|
| T01 | capturas/T01_start_2s_solto.png |
| T02 | capturas/T02_saida_ligada.png |
| T03 | capturas/T03_stop_durante_ET.png |
| T04 | capturas/T04_emergencia_saida_ligada.png |
| T05 | capturas/T05_liberar_falha_sem_start.png |

Observação: no T01, o ET intermediário não foi capturado. O resultado exigido
(Q=0 e MOTOR_DELAY=0) foi comprovado após soltar o START.
