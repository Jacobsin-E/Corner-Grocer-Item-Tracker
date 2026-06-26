# Corner-Grocer-Item-Tracker
A C++ terminal application designed to parse daily purchase records into actionable frequency data and histograms.

Summarize the project and what problem it was solving.
The Corner Grocer project is a C++ terminal application designed to process and analyze daily purchase records. The problem it solves is converting unstructured, chronological text data into actionable metrics. By parsing the daily records into a frequency map, the program allows the grocer to easily identify which items are purchased most often, providing the data needed to optimize the physical layout of the produce section for customers.

What did you do particularly well?
I focused heavily on system stability through robust run-time error handling. Preventative measures in software are critical, so I built failsafes into the terminal interface. The program cleanly catches operator input faults (such as entering a letter instead of an integer for a menu choice), flushes the corrupted input buffer, and prevents the terminal from crashing into an infinite loop.

Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?
Currently, the program relies on flat text files (.txt and .dat) for data loading and backup. To enhance scalability and security, the backend could be transitioned to integrate with a relational database using SQL. Moving away from local text files to a dedicated database would allow for safer, long-term historical tracking of inventory, faster query times across massive datasets, and better data encryption.

Which pieces of the code did you find most challenging to write, and how did you overcome this? What tools or resources are you adding to your support network?
The most challenging element was engineering the input validation fail-safes, specifically handling stream errors when an operator inputs the wrong data type (e.g., typing a character when an integer is expected). Initially, this caused the cin stream to enter a fail state and trigger an infinite crash loop. I overcame this by researching C++ input stream mechanics and implementing cin.clear() to reset the error flag, followed by cin.ignore() to completely flush the corrupted buffer. Moving forward, official C++ documentation regarding standard library stream states will be a permanent fixture in my support network.

What skills from this project will be particularly transferable to other projects or course work?
The object-oriented design principles and input sanitization techniques are highly transferable. Writing code that anticipates operator errors and compartmentalizes core logic into distinct classes is fundamental for building reliable, automated systems. Additionally, the ability to seamlessly parse and write to external files is a core skill I will carry into future software development.

How did you make this program maintainable, readable, and adaptable?
I ensured maintainability through strict organization and rigorous testing. The code utilizes standard camelCase naming conventions and thorough in-line comments designed to act as a clear system blueprint for any future developer. To guarantee adaptability and stability, I incorporated iterative testing, running the program multiple times to actively hunt for edge cases. By deliberately forcing input faults during these testing cycles, I verified that the fail-safes held up under stress. Finally, because the core logic is fully contained within a class, the system is highly adaptable; the backend could easily be plugged into a graphical user interface (GUI) later without needing to rewrite the core logic.
