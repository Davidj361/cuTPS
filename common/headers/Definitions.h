#ifndef DEFINITION_H
#define DEFINITION_H

// TODO remove add chapter and add section
enum commands_t {ADD_TEXTBOOK, EDIT_TEXTBOOK, REMOVE_TEXTBOOK, ADD_COURSE, EDIT_COURSE, REMOVE_COURSE,
                 ADD_CHAPTER, EDIT_CHAPTER, REMOVE_CHAPTER, ADD_SECTION, EDIT_SECTION, REMOVE_SECTION,
                 ADD_INVOICE, GET_CONTENT, LOGIN, ADD_CLASS, EDIT_CLASS, DELETE_CLASS};
enum user_t {STUDENT, CONTENT_MANAGER, ADMINISTRATOR};
enum status_t {SUCCESS, ERROR, REQUEST};

#endif
