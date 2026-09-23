# Atividade Prática - Sistemas Automatizados (Semana 4)

Este repositório contém a implementação e validação da lógica de funcionamento para o acionamento de uma máquina, representada pela expressão booleana:

$$M = S \cdot G \cdot \neg E$$

Onde:
- **S**: Sinal de Start (Entrada)
- **G**: Liberação Geral (Entrada)
- **E**: Emergência (Entrada com negação / contato fechado)
- **M**: Acionamento da Máquina (Saída)

---

## 1. Simulação em Lógica Digital (CircuitVerse)
O circuito lógico foi desenvolvido utilizando portas lógicas (AND e NOT) para validar a expressão matemática.

- **Link do Projeto:** (https://circuitverse.org/users/461952/projects/2041681)
- **Print da Simulação:**
  <img width="1600" height="728" alt="image" src="https://github.com/user-attachments/assets/e351723e-436c-4b4e-8b03-9272e8c00eb8" />


---

## 2. Simulação em Linguagem Ladder (PLC Simulator Online)
O mesmo comportamento foi replicado em ambiente industrial utilizando o simulador de CLP em formato Ladder, empregando contactos abertos em série e um contacto fechado para a segurança de emergência.

- **Link do Projeto:** (https://app.plcsimulator.online/ZsYRjySvJmkdyq2MogoW)

- **Print da Simulação (Ladder):**
  <img width="1600" height="699" alt="image" src="https://github.com/user-attachments/assets/8a223927-3184-4b60-b9aa-c2f3709f6f2a" />
  <img width="1600" height="705" alt="image" src="https://github.com/user-attachments/assets/2ad220cd-a651-4599-b1fd-38aa9e793510" />
  <img width="1600" height="705" alt="image" src="https://github.com/user-attachments/assets/a57825b3-8399-4490-bbd4-817f10858d36" />
  <img width="1600" height="706" alt="image" src="https://github.com/user-attachments/assets/101f3a78-7473-47da-a6d8-ffdc6c02525a" />





---

## 3. Tabela de Verdade
Todas as 8 combinações possíveis foram testadas e validadas em ambos os simuladores, confirmando que a saída $M = 1$ ocorre exclusivamente quando $S=1$, $G=1$ e $E=0$.

| S | G | E | M (Esperado) | Status |
|---|---|---|--------------|--------|
| 0 | 0 | 0 | 0 | Pass |
| 0 | 0 | 1 | 0 | Pass |
| 0 | 1 | 0 | 0 | Pass |
| 0 | 1 | 1 | 0 | Pass |
| 1 | 0 | 0 | 0 | Pass |
| 1 | 0 | 1 | 0 | Pass |
| **1** | **1** | **0** | **1** | **Pass** |
| 1 | 1 | 1 | 0 | Pass |
