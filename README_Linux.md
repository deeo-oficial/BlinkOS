# 🚀 BlinkOS - Mini Serial Operating System

O **BlinkOS** é um sistema operacional minimalista de 8 bits projetado para rodar em hardware limitado (Arduino Uno / ATmega328P). Ele transforma o microcontrolador em um terminal interativo com sistema de arquivos, segurança por senha e um ambiente de execução de baixo nível (Assembly Virtual).

---

## 📋 Especificações Técnicas
* **Kernel:** BlinkOS v1.0.2 Stable
* **Hardware Alvo:** Arduino Uno (ATmega328P)
* **Interface:** Serial Terminal (9600 baud)
* **Armazenamento:** 1024 bytes (EEPROM Interna)
* **Segurança:** Autenticação por senha (Padrão: `1234`)

---

## 💻 Configuração no Linux Mint (T400)

Como o BlinkOS utiliza comunicação serial intensa, siga estes passos no seu terminal para evitar erros de permissão:

1.  **Permissão de Porta:**
    ```bash
    sudo usermod -a -G dialout $USER
    ```
2.  **Liberar Porta Ocupada (Se necessário):**
    ```bash
    sudo fuser -k /dev/ttyUSB0
    ```

---

## 🛠️ Como Instalar

1.  Abra o **Arduino IDE 1.8.19**.
2.  Carregue o código do `blinkOS.ino`.
3.  Configure a placa como **Arduino Uno**.
4.  Clique em **Upload**.
5.  Abra o **Serial Monitor** (Ctrl+Shift+M).
    * **Importante:** Selecione `Both NL & CR` e velocidade `9600 baud`.

---

## 🕹️ Comandos do Sistema

Após realizar o login com a senha `1234`, os seguintes comandos estarão disponíveis:

| Comando | Função | Exemplo |
| :--- | :--- | :--- |
| `help` | Lista todos os comandos | `help` |
| `calc` | Calculadora (sem espaços) | `15*3` ou `100/5` |
| `edit` | Escreve uma nota no Disco A | `edit` -> [seu texto] |
| `type` | Lê a nota salva na EEPROM | `type` |
| `del` | Formata o armazenamento | `del` |
| `asm` | Compilador Assembly Virtual | `asm` |
| `free` | Checa RAM disponível | `free` |
| `cls` | Limpa a tela do terminal | `cls` |
| `logout` | Bloqueia o sistema | `logout` |

---

## 🧑‍💻 Tutorial Assembly (ASM Mode)

O BlinkOS v1.0.2 permite simular operações de baixo nível usando dois registradores virtuais (**RA** e **RB**).

1.  Digite `asm` para entrar no modo de compilação.
2.  Use `MOV RA,10` para definir um valor.
3.  Use `ADD RA,RB` para somar os registradores.
4.  Use `SHOW` para ver o estado atual da CPU virtual.
5.  Digite `EXIT` para retornar ao Shell principal.

---
**Desenvolvido por:** DEEO
**Hardware:** Lenovo T400 | Linux Mint "Zena"
