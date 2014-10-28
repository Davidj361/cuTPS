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
SELECT * FROM `Users`;

INSERT INTO `Users` (username, password, type, name) VALUES ('admin', 'password123', 'administrator', 'Administrator');

SELECT * FROM `Users`;
END TRANSACTION;