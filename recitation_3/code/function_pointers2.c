#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person {
    int age;
} Person;

int compare_people_age(const void *p1, const void *p2) {
    return ((Person *)p1)->age - ((Person *)p2)->age;
}

int main() {
    Person p1;
    p1.age = 21;
    Person p2;
    p2.age = 22;
    Person p3;
    p3.age = 20;
    Person people[3] = {p1, p2, p3};
    qsort(people, 3, sizeof(Person), compare_people_age);

    for (int i = 0; i < 3; i++) {
        printf("%d\n", people[i].age);
    }
}