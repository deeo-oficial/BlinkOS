# 🚀 BlinkOS - Mini Serial Operating System (Windows Guide)

O **BlinkOS** é um sistema operacional de 8 bits para Arduino Uno. Este guia foca na configuração e execução dentro do ambiente Windows (7, 10 ou 11).

---

## 📋 Especificações
* **Kernel:** BlinkOS v1.0.2 Stable
* **Hardware:** Arduino Uno (ATmega328P)
* **Interface:** Serial Terminal (9600 baud)
* **Senha Padrão:** `1234`

---

## ⚙️ Configuração no Windows

### 1. Drivers (O Passo Mais Importante)
Se o seu Arduino for um modelo compatível (clone), o Windows pode não reconhecê-lo de primeira.
* Verifique o chip perto da porta USB do Arduino.
* Se for o **CH340**, baixe e instale o "CH341SER Driver".
* Se for **FTDI**, o Windows Update geralmente instala sozinho, mas você pode baixar o "VCP Driver" no site oficial da FTDI.

### 2. Identificando a Porta COM
No Windows, as portas não se chamam /dev/tty. 
1. Clique com o botão direito no menu **Iniciar** e vá em **Gerenciador de Dispositivos**.
2. Expanda a seção **Portas (COM e LPT)**.
3. Anote o número da porta (Ex: `COM3`, `COM4`).

---

## 🛠️ Instalação (Arduino IDE)

1. Abra o **Arduino IDE** no seu PC.
2. Cole o código fonte do `blinkOS.ino`.
3. Vá em **Ferramentas > Placa** e selecione `Arduino Uno`.
4. Vá em **Ferramentas > Porta** e selecione a porta `COM` que você anotou.
5. Clique no botão de **Seta (Carregar)**.

---

## 🕹️ Operação do Sistema

Para usar o BlinkOS no Windows, abra o **Monitor Serial** (Ctrl+Shift+M) e configure:

* **Baud Rate:** `9600 baud`
* **Final de Linha:** `Ambos, NL e CR` (Crucial para o sistema aceitar os comandos).

### Lista de Comandos:
* `help`: Menu de ajuda.
* `calc`: Calculadora inteligente (Ex: `12*5`).
* `edit`: Bloco de notas (salva na EEPROM).
* `type`: Lê a nota salva.
* `asm`: Entra no modo Assembly Virtual.
* `free`: Checa a memória RAM do chip.
* `logout`: Bloqueia o sistema com senha.

---

## 🆘 Solução de Problemas (Windows)

**Erro: "Porta já está em uso" (Access is denied):**
* No Windows, apenas um programa pode usar a porta COM por vez. Feche outros monitores seriais, Cura (fatiador 3D) ou o terminal antes de tentar carregar o código.

**Caracteres Estranhos no Monitor:**
* Verifique se a velocidade está em `9600 baud`. Se estiver diferente, você verá símbolos sem sentido.

**Teclado não digita:**
* Certifique-se de que a caixa de texto no topo do Monitor Serial está selecionada antes de começar a digitar.

---
**Desenvolvido por:** DEEO
**Build:** v1.0.2 Stable
