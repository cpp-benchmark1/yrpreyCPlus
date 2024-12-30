# YrpreyC++

![yprey](https://i.imgur.com/rF7RaMD.png)

**Programs created by [Fernando Mengali](https://www.linkedin.com/in/fernando-mengali-273504142/)**

YrpreyC++ is a framework written in the C++ language that contains vulnerabilities related to memory issues, categorized as overflows. The framework was developed for individuals interested in teaching and learning more about Pentesting (penetration testing) and Application Security. 

In the context of Offensive Security, vulnerabilities present in web applications can be identified, exploited, and compromised. For professionals and experts in application security, the framework provides an in-depth understanding of vulnerabilities at the code level.

Currently, Yrprey is one of the frameworks in C++ with the highest number of memory-related vulnerabilities worldwide, making it valuable for educational, learning, and teaching purposes in the field of Information Security. For more information about the vulnerabilities, we recommend exploring the available details on [yrprey.com](https://yrprey.com).

#### Features
 - Based on OWASP A5 from 2003 and 2005.

 - A5: Overflow Vulnerability Categories

 - A6: Injection Flaws

#### List of Vulnerabilities

In this section, we have a comparison of vulnerabilities categorized by overflow with compiled code files and vulnerable software. This table makes it easier to understand how to exploit vulnerabilities in each system function. 
This table aims to facilitate theoretical understanding to be able to exploit vulnerabilities. Once the scenario is understood, the process of identifying and exploiting vulnerabilities becomes easier. 
If you are an Application Security professional, knowing the scenario and overflow vulnerabilities facilitates the vulnerability remediation process with manual Code Review Security techniques or automated analyses like SAST (Static Application Security Testing).

This table compares different types of vulnerabilities, detailing the specific vulnerable point, vulnerability description, the vulnerable software involved, and the vulnerabilities associated with each vulnerable point. Each row provides clear information about the type of vulnerability and how it relates to a specific software or system:

|  Numb  |   **OWASP TOP 10 2003 e 2004**    |    **File Source**      |    **Executable**      |            **Details**                                 |
|-------:|:---------------------------------:|:-----------------------:|:----------------------:|:------------------------------------------------------:|
|   01   |   A05: Buffer Overflow Vanilla    |   bufferOverflow.cpp    |  bufferOverflow.exe    |    Buffer Overflow and Privilege Escalation            |
|   02   |     A06: Injection Flaws          |   commandInjection.cpp  |  commandInjection.exe  |    Use a pipe and execute OS commands.                 |
|   03   |      A05: Format String           |   formatString.cpp      |  formatString.exe      |    Provide a malicious string and escalate privilege.  |
|   04   |     A05: Memory Leaks             |   memoryLeaks.cpp       |  memoryLeaks.exe       |    Overflow a buffer causing Denial of Service.        |
|   05   |  A05: Improper Null Termination   |   improperNulTerm.cpp   |  improperNulTerm.exe   |    Exploit Improper Null Termination, Write to Memory, and Escalate Privileges  |
|   06   |        A05: Heap Overflow         |   heapOverflow.cpp      |  heapOverflow.exe      |    Heap Overflow and Privilege Escalation              |
|   07   |      A05: Integer Overflow        |   integerOverflow.cpp   |  integerOverflow.exe   |    Cause an Integer Overflow and Escalate Privileges   |
|   08   |      A05: Integer Underflow       |   integerUnderflow.cpp  |  integerUnderflow.exe  |    Cause an Integer Underflow and Escalate Privileges  |


## How to exploit vulnerability number 01 from the table (Buffer Overflow Vanilla)

![yprey](https://i.imgur.com/Fu11OXu.png)

01 - Execute the program vulnerable

![yprey](https://i.imgur.com/tgbWxCW.png)

02 - Execute Immunity Debugger

![yprey](https://i.imgur.com/er9NIog.png)

03 - Open the executable bufferOverflow.exe on Immunity Debugger

![yprey](https://i.imgur.com/RiZzhi3.png)

04 - Type 50 chacteres "A" and look the Buffer Overflow

![yprey](https://i.imgur.com/JjY4pXh.png)

05 - Use the command to generate string with 50 chacteres on Kali Linux:

```
msf-pattern_create -l 50
```

![yprey](https://i.imgur.com/voEeZfH.png)

06 - Open the program again and load Immunity Debugger as in step 03.
Enter a string at the Windows command prompt and press ENTER
The EIP value is 62413961.

![yprey](https://i.imgur.com/GKXSTSu.png)

07 - In Kali Linux, run the msf-pattern_offset command to get the threshold value up to the EIP:

```
msf-pattern_offset -q 62413961
```

![yprey](https://i.imgur.com/OCsdWsg.png)

08 - Type 28 chacteres "A", after 4 characters "B" and 20 characters "C".

Look the Buffer Overflow: EIP have 4 characters "B".

To successfully execute a calculator or perform another action on Windows, we recommend studying how the EIP manipulation process works for Vanilla Buffer Overflow.


## How to exploit vulnerability number 02 from the table (Command Injection)

![yprey](https://i.imgur.com/gaP7BEO.png)

01 - Enter the directory or folder name followed by the pipe character and a system-level operating system command, for example, "ipconfig".

## How to exploit vulnerability number 03 from the table (Format String)

![yprey](https://i.imgur.com/txVOze3.png)

01 - Enter more than 20 characters to gain visibility into the memory issue related to Format String..


## How to exploit vulnerability number 04 from the table (Memory Leak)

![yprey](https://i.imgur.com/K6tpSkt.png)

01 - Access to the program to check memory leakage and consumption.


## How use

* Download the source code and compile it on a Windows operating system.
* Download the binaries and execute them to exploit the vulnerabilities.

## Observation
Test on the Windows XP operating system.

## Reporting Vulnerabilities

Please, avoid taking this action and requesting a CVE!

The application intentionally has some vulnerabilities, most of them are known and are treated as lessons learned. Others, in turn, are more "hidden" and can be discovered on your own. If you have a genuine desire to demonstrate your skills in finding these extra elements, we suggest you share your experience on a blog or create a video. There are certainly people interested in learning about these nuances and how you identified them. By sending us the link, we may even consider including it in our references.
