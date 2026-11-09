# Vole Machine Simulator 🖥️

## 📌 Description
This program simulates how a computer (Von Neumann architecture) operates at a low level, developed as a collaborative team project for our computer organization course at **Cairo University - Faculty of Computers and Artificial Intelligence (FCAI)**.

---

## 🏛️ Academic Information
* **University:** Cairo University
* **Faculty:** Computers and Artificial Intelligence (FCAI)
* **Department / Program:** Computer Science / Artificial Intelligence
* **Course Name:** Computer Organization / Architecture
* **Course Instructor:** Dr. Mohamed El-Ramly
* **Teaching Assistant (TA):** Eng. Hager
* **Project Name:** Vole Machine Simulator

---

## 👥 Team Members, IDs & Sections
1. **Mai Sabry Shappan Atiya** — ID: `20242360` — Section: `39, 40`
2. **Sara Yasser Abdelmotelb** — ID: `20250275` — Section: `39, 40`
3. **Baher Yasser Ayad** — ID: `20250114` — Section: `39, 40`
4. **Ahmed Mohamed Ramadan** — ID: `20250052` — Section: `39, 40`

---

## ⚙️ Instruction Set
For a working example, check the provided `.txt` file inside the repository.

* **1 *Load*:** Provided with a register and memory address; the value in the memory is **loaded into** the register.
* **2 *Load*:** Provided with a register and a bit pattern in **hexa** format; the bit pattern is **loaded into** the register.
* **3 *Store*:** Provided with a register and memory address; the value of the register is **stored in** the memory. *(If memory address is 0, the value is printed to the screen)*.
* **4 *Move*:** Provided with two registers (R & S); the value in R is **moved** into S.
* **5 *Add*:** Provided with three registers (R, S & T); the integer result of **adding** S and T is stored in R.
* **6 *Add*:** Provided with three registers (R, S & T); the float result of **adding** S and T is stored in R.
* **7 *OR*:** Provided with three registers (R, S & T); the result of **bitwise OR-ing** S and T is stored in R.
* **8 *AND*:** Provided with three registers (R, S & T); the result of **bitwise AND-ing** S and T is stored in R.
* **9 *XOR*:** Provided with three registers (R, S & T); the result of **bitwise XOR-ing** S and T is stored in R.
* **A *ROTATE*:** Provided with a register and a bit pattern in **hexa**; the register is **bitwise rotated** according to the given pattern.
* **B *Jump*:** Provided with a register and memory address; if the value in the register **equals** register 0, the program counter jumps to the given memory address.
* **C *Halt*:** Signals the machine to **stop** executing the program.
* **D *Jump*:** Provided with a register and memory address; if the value in the register is **strictly less than** register 0, the program counter jumps to the given memory address.

---

## 🛠️ Compilation
To compile and run the project, use one of the following methods:

* **Using G++ (Terminal / Command Prompt):**
  ```bash
  g++ -o main.exe *.cpp
