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
    `id` INTEGER NOT NULL PRIMARY KEY,
    `name` TEXT NOT NULL,
    `number` INTEGER NOT NULL,
    `textbook` TEXT NOT NULL,
    `description` TEXT,
    `availability` INTEGER NOT NULL,
    `price` REAL NOT NULL,
    `content_id` INTEGER NOT NULL,
    FOREIGN KEY(`textbook`) REFERENCES Textbooks(`isbn`),
    FOREIGN KEY(`content_id`) REFERENCES Content(`id`)
);

CREATE TABLE IF NOT EXISTS `Sections` (
    `id` INTEGER NOT NULL PRIMARY KEY,
    `name` TEXT NOT NULL,
    `number` INTEGER NOT NULL,
    `chapter` INTEGER NOT NULL,
    `description` TEXT,
    `availability` INTEGER NOT NULL,
    `price` REAL NOT NULL,
    `content_id` INTEGER NOT NULL,
    FOREIGN KEY(`chapter`) REFERENCES Chapters(`id`),
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
INSERT INTO `Courses` (code, name) VALUES ('SPAN 2415', 'Natural Disasters');

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


END TRANSACTION;