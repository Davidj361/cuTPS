PRAGMA foreign_keys = ON;

CREATE TABLE IF NOT EXISTS `Users` (
    `username` TEXT NOT NULL PRIMARY KEY,
    `password` TEXT NOT NULL,
    `type` TEXT NOT NULL,
    `name` TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS `Courses` (
    `code` TEXT NOT NULL PRIMARY KEY,
    `name` TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS `Content` (
    `id` INTEGER NOT NULL PRIMARY KEY
);

CREATE TABLE IF NOT EXISTS `Textbooks` (
    `isbn` TEXT NOT NULL PRIMARY KEY,
    `title` TEXT NOT NULL,
    `publisher` TEXT NOT NULL,
    `author` TEXT NOT NULL,
    `year` INTEGER NOT NULL,
    `edition` TEXT,
    `description` TEXT,
    `availability` INTEGER NOT NULL,
    `price` REAL NOT NULL,
    `content_id` INTEGER NOT NULL,
    FOREIGN KEY(`content_id`) REFERENCES Content(`id`)
);

CREATE TABLE IF NOT EXISTS `Chapters` (
    `name` TEXT NOT NULL,
    `number` INTEGER NOT NULL,
    `textbook` TEXT NOT NULL,
    `description` TEXT,
    `availability` INTEGER NOT NULL,
    `price` REAL NOT NULL,
    `content_id` INTEGER NOT NULL,
    PRIMARY KEY(`number`, `textbook`),
    FOREIGN KEY(`textbook`) REFERENCES Textbooks(`isbn`),
    FOREIGN KEY(`content_id`) REFERENCES Content(`id`)
);

CREATE TABLE IF NOT EXISTS `Sections` (
-- exi    `id` INTEGER UNIQUE,
    `name` TEXT NOT NULL,
    `number` INTEGER NOT NULL,
    `chapter` INTEGER NOT NULL,
    `textbook` TEXT NOT NULL,
    `description` TEXT,
    `availability` INTEGER NOT NULL,
    `price` REAL NOT NULL,
    `content_id` INTEGER NOT NULL,
    PRIMARY KEY(`number`, `chapter`, `textbook`),
    FOREIGN KEY(`content_id`) REFERENCES Content(`id`)
);

CREATE TABLE IF NOT EXISTS `Book_List` (
    `textbook_id` TEXT NOT NULL,
    `course_code` TEXT NOT NULL,
    PRIMARY KEY(`textbook_id`, `course_code`),
    FOREIGN KEY(`textbook_id`) REFERENCES Textbooks(`isbn`),
    FOREIGN KEY(`course_code`) REFERENCES Courses(`code`)
);

CREATE TABLE IF NOT EXISTS `Class_List` (
    `student` TEXT NOT NULL,
    `course_code` TEXT NOT NULL,
    PRIMARY KEY(`student`, `course_code`),
    FOREIGN KEY(`student`) REFERENCES Users(`username`),
    FOREIGN KEY(`course_code`) REFERENCES Courses(`code`)
);

CREATE TABLE IF NOT EXISTS `Invoices` (
    `id` INTEGER NOT NULL PRIMARY KEY,
    `student` TEXT NOT NULL,
    `date_purchased` TEXT NOT NULL,
    FOREIGN KEY(`student`) REFERENCES Users(`username`)
);

CREATE TABLE IF NOT EXISTS `Purchases` (
    `invoice_id` INTEGER NOT NULL,
    `content_id` INTEGER NOT NULL,
    PRIMARY KEY(`invoice_id`, `content_id`),
    FOREIGN KEY(`invoice_id`) REFERENCES Invoices(`id`),
    FOREIGN KEY(`content_id`) REFERENCES Content(`id`)
);

BEGIN TRANSACTION;

-- Create an administrator
INSERT INTO `Users` (username, password, type, name) VALUES ('admin', 'password', 'administrator', 'Administrator');

-- Create some students
INSERT INTO `Users` (username, password, type, name) VALUES ('bruce', 'password', 'student', 'Bruce Wayne');
INSERT INTO `Users` (username, password, type, name) VALUES ('peter', 'password', 'student', 'Peter Parker');
INSERT INTO `Users` (username, password, type, name) VALUES ('clark', 'password', 'studentd', 'Clark Kent');
INSERT INTO `Users` (username, password, type, name) VALUES ('celina', 'password', 'student', 'Celina Kyle');

-- Create some content managers
INSERT INTO `Users` (username, password, type, name) VALUES ('gandalf', 'password', 'content_manager', 'Gandalf the Grey');
INSERT INTO `Users` (username, password, type, name) VALUES ('albus', 'password', 'content_manager', 'Albus Dumbledore');

-- Create some courses
INSERT INTO `Courses` (code, name) VALUES ('COMP 1405', 'Introduction to Computer Science I');
INSERT INTO `Courses` (code, name) VALUES ('COMP 1406', 'Introduction to Computer Science II');
INSERT INTO `Courses` (code, name) VALUES ('COMP 1805', 'Discrete Structures I');
INSERT INTO `Courses` (code, name) VALUES ('COMP 2401', 'Introduction to Systems Programming');
INSERT INTO `Courses` (code, name) VALUES ('COMP 2402', 'Abstract Data Types and Algorithms');
INSERT INTO `Courses` (code, name) VALUES ('MATH 2007', 'Elementary Calculus II');
INSERT INTO `Courses` (code, name) VALUES ('MATH 1104', 'Linear Algebra');
INSERT INTO `Courses` (code, name) VALUES ('PSCI 1100', 'Introduction to Political Science I');
INSERT INTO `Courses` (code, name) VALUES ('ERTH 2401', 'Dinosaurs');
INSERT INTO `Courses` (code, name) VALUES ('ERTH 2415', 'Natural Disasters');

-- Create some textbooks
INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Textbooks` (isbn, title, publisher, author, year, edition, description, availability, price, content_id)
    VALUES ('0123736021', 'Learning Processing', 'Morgan Kaufmann', 'Daniel Shiffman', 2008, '1', 'A Beginners Guide to Programming Images, Animation, and Interaction', 1,  58.82,  (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Textbooks` (isbn, title, publisher, author, year, edition, description, availability, price, content_id)
    VALUES ('0071808558', 'Java: The Complete Reference', 'McGraw-Hill Osborne Media', 'Herbert Schild', 2014, '9', 'The Definitive Java Programming Guide', 1,  40.09,  (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Textbooks` (isbn, title, publisher, author, year, edition, description, availability, price, content_id)
    VALUES ('1906574820', 'Discrete Structure', 'New Academic Science Ltd', 'B. S. Vatsa', 2012, '4', NULL, 1, 55, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Textbooks` (isbn, title, publisher, author, year, edition, description, availability, price, content_id)
    VALUES ('0136067123', 'System Programming with C and Unix', 'Addison-Wesley', 'Adam Hoover', 2009, '1', 'Adam Hoover''s System Programming with C and Unix introduces students to commonly used system tools (libraries, debuggers, system calls, shells and scripting languages) and then explains how to utilize these tools to optimize program development.  The text also examines lower level data types with an emphasis on memory and understanding how and why different data types are used.', 1, 131.40, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Textbooks` (isbn, title, publisher, author, year, edition, description, availability, price, content_id)
    VALUES ('1927356385', 'Open Data Structures: An Introduction', 'AU Press', 'Pat Morin', 2013, '', 'Offered as an introduction to the field of data structures and algorithms, Open Data Structures covers the implementation and analysis of data structures for sequences (lists), queues, priority queues, unordered dictionaries, ordered dictionaries, and graphs. Focusing on a mathematically rigorous approach that is fast, practical, and efficient, Morin clearly and briskly presents instruction along with source code.', 1, 29.95, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Textbooks` (isbn, title, publisher, author, year, edition, description, availability, price, content_id)
    VALUES ('0538498676', 'Single Variable Calculus: Early Transcendentals', 'Brooks Cole', 'James Stewart', 2011, '7', '', 1, 147.68, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Textbooks` (isbn, title, publisher, author, year, edition, description, availability, price, content_id)
    VALUES ('9780538735452', 'Linear Algebra: A Modern Introduction ', 'Brooks Cole', 'David Poole', 2010, '3', 'Poole''s approach helps students succeed in this course by learning vectors and vector geometry first in order to visualize and understand the meaning of the calculations that they will encounter and develop mathematical maturity for thinking abstractly.', 1, 196.95, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Textbooks` (isbn, title, publisher, author, year, edition, description, availability, price, content_id)
    VALUES ('0030740169', 'History of Political Theory: An Introduction to Ancient and Medieval Political Theory, Volume 1', 'Wadsworth Publishing', 'George Klosko', 1994, '1', 'This text covers the essential political ideas of major theorists. Extensive quoted material - taken from the works of dominant figures in ancient and medieval political thought - makes this text a flexible, scholarly alternative for instructors who don''t want to require their students to purchase a library of original works.', 1, 124.68, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Textbooks` (isbn, title, publisher, author, year, edition, description, availability, price, content_id)
    VALUES ('0521282373', 'Dinosaurs: A Concise Natural History', 'Cambridge University Press', 'David E. Fastovsky, David B. Weishampel', 2012, '2', '', 1, 68.54, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Textbooks` (isbn, title, publisher, author, year, edition, description, availability, price, content_id)
    VALUES ('0070385491', 'Natural Disasters', 'McGraw-Hill Ryerson Higher Education', ' Patrick Leon Abbott, Claire Samson', 2012, 'Canadian Edition', 'Abbott/Samson Natural Disasters, Second Canadian Edition, focuses on explaining how the normal processes of the earth concentrate their energies and wreak havoc on civilization', 1, 144.95, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Textbooks` (isbn, title, publisher, author, year, edition, description, availability, price, content_id)
    VALUES ('0199557608', 'King James Bible: 400th Anniversary Edition', 'Oxford University Press', 'Oxford', 2010, '400th Anniversary edition', 'This 400th anniversary edition of the King James Version of the Bible is a reprint of the 1611 text, in an easy-to-read roman font instead of the black-letter type of the original. The original capital letters, many of which are pictoral, have been restored to each chapter in order to replicate the visual appeal of the early editions. The 1611 text is followed page-for-page and line-for-line, and all misprints are reproduced rather than corrected. The large body of preliminary matter,which includes genealogies, maps, and lists of readings, is also included. The text of the 1611 edition differs from modern editions of the King James Version in thousands of details, and this edition is the most authentic version of the original text that has ever been published. The volume concludes with an essay by Gordon Campbell on the first edition of the King James Bible.', 0, 56.67, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Textbooks` (isbn, title, publisher, author, year, edition, description, availability, price, content_id)
    VALUES ('1879402297', 'The Qur''an: A Translation', 'Tahrike Tarsile Qur''an', 'Abdullah Yusuf Ali', 2001, '10', 'This English translation of the Qur''an is a compilation of the Muslim faith''s Final Revelation from God to mankind through the last Prophet Muhammad, Peace be upon Him. The Qur''an has a wealth of information--both worldly wisdom and intellectual concepts--providing a code of life for humankind generally and Muslims in particular. Indeed, the Qur''an''s miracle lies in its ability to offer something to non-believers and everything to believers.', 0, 11.68, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Textbooks` (isbn, title, publisher, author, year, edition, description, availability, price, content_id)
    VALUES ('082760680X', 'The Torah, Pocket Edition', 'The Jewish Publication Society', 'Inc. Jewish Publication Society', 1999, 'Pocket Edition', 'The Torah is the essence of Jewish tradition; it inspires each successive generation. The current JPS translation, based on classical and modern sources, is acclaimed for its fidelity to the ancient Hebrew.', 0, 15.12, (SELECT last_insert_rowid()));

-- Create some chapters
INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Features', 1, '0123736021', 'Features of the Processing programming language.', 1, 15, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Examples', 2, '0123736021', 'Basic Processing examples.', 1, 15, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Related Projects', 3, '0123736021', 'Projects using the Processing language.', 1, 20, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('History', 1, '0071808558', 'A history of the Java programming language.', 1, 10, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Practices', 2, '0071808558', 'How Java works.', 1, 10, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Syntax', 3, '0071808558', 'Java syntax.', 1, 15, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Grand challenges, past and present', 1, '1906574820', 'Challenges in the field of discrete mathematics.', 1, 9, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Topics in discrete mathematics', 2, '1906574820', '', 1, 15, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Overview', 1, '0136067123', 'An overview of systems programming', 1, 20, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('History', 2, '0136067123', 'A history of systems programming', 1, 20, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Introduction', 1, '1927356385', 'An introduction to data structures', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Array-based Lists', 2, '1927356385', 'Implementations of the List and Queue interfaces', 1, 10, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Linked Lists', 3, '1927356385', 'Implementations of the List interface', 1, 10, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Skip Lists', 4, '1927356385', 'Theory and implementation of the skip list data structure', 1, 10, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Introduction to Single Variable Calculus', 1, '0538498676', '', 1, 20, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Derivatives', 2, '0538498676', 'Calculating the derivative of a function', 1, 30, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Integrals', 3, '0538498676', 'Performing function integrations', 1, 30, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('History', 1, '9780538735452', 'The history of linear algebra', 1, 20, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Scope of study', 2, '9780538735452', '', 1, 30, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Theorems', 3, '9780538735452', 'Useful theorems to remember', 1, 30, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('History', 1, '0030740169', 'The history of political theories', 1, 15, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Contemporary political philosophy', 2, '0030740169', '', 1, 25, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Influential political philosophers', 3, '0030740169', '', 1, 25, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Etymology', 1, '0521282373', 'The taxonomy of dinosaurs', 1, 8.50, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Definition', 2, '0521282373', 'What is a dinosaur?', 1, 10.50, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Evolutionary History', 3, '0521282373', 'Where did dinosaurs come from?', 1, 13.50, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Avalanches', 1, '0070385491', 'Anatomy of an avalanche', 1, 15.50, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Volcanic Eruptions', 2, '0070385491', 'Dissecting an eruption', 1, 15.50, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Earthquakes', 3, '0070385491', 'Earthquake shakedown', 1, 15.50, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Old Testament', 1, '0199557608', '', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('New Testament', 2, '0199557608', '', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Monotheism', 1, '1879402297', '', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Eschatology', 2, '1879402297', '', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Prophets', 3, '1879402297', '', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Genesis', 1, '082760680X', '', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Exodus', 2, '082760680X', '', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Chapters` (name, number, textbook, description, availability, price, content_id) 
    VALUES ('Leviticus', 3, '082760680X', '', 1, 5, (SELECT last_insert_rowid()));
    
-- Create some Sections
INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Hello World', 1, 2, '0123736021', 'A basic Hello World example in Processing', 1, 2, (SELECT last_insert_rowid()));
    
INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('United States presidential election map', 2, 2, '0123736021', 'How to draw a United States presidential election map in Processing', 1, 2, (SELECT last_insert_rowid()));
    
INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Design By Numbers', 1, 3, '0123736021', '', 1, 5, (SELECT last_insert_rowid()));
    
INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Wiring, Arduino, and Fritzing', 3, 3, '0123736021', '', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Principles', 1, 1, '0071808558', 'Principles of the Java programming language', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Versions', 2, 1, '0071808558', 'Versions of the Java programming language', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Java Platform', 1, 2, '0071808558', 'Implementations and performance of the Java programming language', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Automatic Memory Management', 2, 2, '0071808558', 'Memory management and garbage collection in Java', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Theoretical Computer Science', 1, 2, '1906574820', 'Discrete structures in Computer Science', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Information Theory', 2, 2, '1906574820', 'Discrete structures in Information Theory', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Logic', 3, 2, '1906574820', 'Discrete structures in Logic', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Set Theory', 4, 2, '1906574820', 'Discrete structures in Set Theory', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Combinatorics', 5, 2, '1906574820', 'Discrete structures in Combinatorics', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('The Need for Efficiency', 1, 1, '1927356385', 'Why efficiency is important', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Interfaces', 2, 1, '1927356385', 'The differences between a data structures interface and its implementation', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Mathematical Backgroud', 3, 1, '1927356385', 'Mathematical notation used to throughout this book', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Array Stack', 1, 2, '1927356385', 'Fast stack operations using an array', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Fast Array Stack', 2, 2, '1927356385', 'An optimized Array Stack', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Array Queue', 3, 2, '1927356385', 'An array-based queue', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Array Deque', 4, 2, '1927356385', 'Fast deque operations using an array', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Dual Array Deque', 5, 2, '1927356385', 'Building a deque from two stacks', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Rootish Array Stack', 6, 2, '1927356385', 'A space efficient array stack', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('SLList', 1, 3, '1927356385', 'Singly linked lists', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('DLList', 2, 3, '1927356385', 'Doubly linked lists', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('SEList', 3, 3, '1927356385', 'A space efficient linked list', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Basic Structure', 1, 4, '1927356385', '', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Skiplist SSet', 2, 4, '1927356385', 'An efficient SSet', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Skiplist List', 3, 4, '1927356385', 'An efficient random-access list', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Analysis of Skip Lists', 4, 4, '1927356385', '', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Educational History', 1, 1, '9780538735452', 'An educational of linear algebra', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Vector Spaces', 1, 2, '9780538735452', '', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Linear Transformations', 2, 2, '9780538735452', '', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Subspaces, span and basis', 3, 2, '9780538735452', '', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Matrix Theory', 4, 2, '9780538735452', 'Follow the white rabbit Neo', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Eigenvalues and Eigenvectors', 5, 2, '9780538735452', '', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Inner-product Spaces', 6, 2, '9780538735452', '', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Ancient Philosophies', 1, 1, '0030740169', 'Political Theory of ancient philosophies', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Medieval Christianity', 2, 1, '0030740169', 'Political Theory of medieval christianity', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Islamic Golden Age', 3, 1, '0030740169', 'Political Theory of the Islamic Golden Age', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Medieval Europe', 4, 1, '0030740169', 'Political Theory of medieval Europe', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('European Renaissance', 5, 1, '0030740169', 'Political Theory of the European Renaissance', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('European Enlightenment', 6, 1, '0030740169', 'Political Theory of the European Enlightenment', 1, 5, (SELECT last_insert_rowid()));    

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Industrialization and the Modern Era', 7, 1, '0030740169', 'Political Theory of the modern era', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('General Description', 1, 2, '0521282373', 'General description of what makes a Dinosaur', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Distinguishing Anatomical Features', 2, 2, '0521282373', 'Distinguishing features of dinosaurs', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Origins and Early Evolution', 1, 3, '0521282373', '', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Evolution and Paleobiogeography', 2, 3, '0521282373', '', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Prophetic Era', 1, 2, '1879402297', '', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Compilation', 2, 2, '1879402297', '', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Worship', 1, 3, '1879402297', '', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('In Islamic Art', 2, 3, '1879402297', '', 1, 5, (SELECT last_insert_rowid()));

INSERT INTO `Content` DEFAULT VALUES;
INSERT INTO `Sections` (name, number, chapter, textbook, description, availability, price, content_id) 
    VALUES ('Inimitability', 3, 3, '1879402297', '', 1, 5, (SELECT last_insert_rowid()));

-- Link Courses to Books
INSERT INTO `Book_List` (textbook_id, course_code) VALUES ('0123736021', 'COMP 1405');
INSERT INTO `Book_List` (textbook_id, course_code) VALUES ('0071808558', 'COMP 1406');
INSERT INTO `Book_List` (textbook_id, course_code) VALUES ('1906574820', 'COMP 1805');
INSERT INTO `Book_List` (textbook_id, course_code) VALUES ('0136067123', 'COMP 2401');
INSERT INTO `Book_List` (textbook_id, course_code) VALUES ('1927356385', 'COMP 2402');
INSERT INTO `Book_List` (textbook_id, course_code) VALUES ('0538498676', 'MATH 2007');
INSERT INTO `Book_List` (textbook_id, course_code) VALUES ('9780538735452', 'MATH 1104');
INSERT INTO `Book_List` (textbook_id, course_code) VALUES ('0030740169', 'PSCI 1100');
INSERT INTO `Book_List` (textbook_id, course_code) VALUES ('0521282373', 'ERTH 2401');
INSERT INTO `Book_List` (textbook_id, course_code) VALUES ('0070385491', 'ERTH 2415');

-- Link Courses to Students
INSERT INTO `Class_List`(student, course_code) VALUES ('bruce', 'COMP 1405');
INSERT INTO `Class_List`(student, course_code) VALUES ('bruce', 'COMP 1406');
INSERT INTO `Class_List`(student, course_code) VALUES ('bruce', 'PSCI 1100');
INSERT INTO `Class_List`(student, course_code) VALUES ('bruce', 'ERTH 2401');
INSERT INTO `Class_List`(student, course_code) VALUES ('peter', 'COMP 1405');
INSERT INTO `Class_List`(student, course_code) VALUES ('peter', 'COMP 1406');
INSERT INTO `Class_List`(student, course_code) VALUES ('peter', 'MATH 1104');
INSERT INTO `Class_List`(student, course_code) VALUES ('peter', 'ERTH 2415');
INSERT INTO `Class_List`(student, course_code) VALUES ('clark', 'COMP 1805');
INSERT INTO `Class_List`(student, course_code) VALUES ('clark', 'COMP 1406');
INSERT INTO `Class_List`(student, course_code) VALUES ('clark', 'MATH 2007');
INSERT INTO `Class_List`(student, course_code) VALUES ('clark', 'PSCI 1100');
INSERT INTO `Class_List`(student, course_code) VALUES ('celina', 'COMP 2401');
INSERT INTO `Class_List`(student, course_code) VALUES ('celina', 'COMP 2402');
INSERT INTO `Class_List`(student, course_code) VALUES ('celina', 'MATH 1104');
INSERT INTO `Class_List`(student, course_code) VALUES ('celina', 'ERTH 2401');

END TRANSACTION;
