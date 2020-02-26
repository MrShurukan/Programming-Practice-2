#pragma once

typedef void (*voidptr)();

// Принимает номер таска и возвращает указатель на функцию
voidptr pickTask(int number);