#include <stdio.h>
#include <time.h>

struct Date {
    int day;
    int month;
    int year;
};

int isLeapYear(int year) {
    return (year % 400 == 0 ||
           (year % 4 == 0 && year % 100 != 0));
}

int daysInMonth(int month, int year) {
    int days[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    if (month == 2 && isLeapYear(year))
        return 29;

    return days[month - 1];
}

int isValidDate(struct Date d) {
    if (d.year < 1 || d.month < 1 ||
        d.month > 12 || d.day < 1)
        return 0;

    return d.day <= daysInMonth(d.month, d.year);
}

int main() {
    struct Date dob, today, age;
    time_t now = time(NULL);
    struct tm *current = localtime(&now);

    if (current == NULL) {
        printf("Unable to get current date.\n");
        return 1;
    }

    today.day = current->tm_mday;
    today.month = current->tm_mon + 1;
    today.year = current->tm_year + 1900;

    printf("===== AGE CALCULATOR =====\n");
    printf("Enter your Date of Birth (DD MM YYYY): ");
    
    if (scanf("%d %d %d",
        &dob.day, &dob.month, &dob.year) != 3) {
        printf("Invalid input!\n");
        return 1;
    }

    if (!isValidDate(dob)) {
        printf("Invalid date of birth!\n");
        return 1;
    }

    if (dob.year > today.year ||
        (dob.year == today.year &&
         dob.month > today.month) ||
        (dob.year == today.year &&
        
        
         dob.month == today.month &&
         dob.day > today.day)) {
        printf("Date of birth cannot be in the future!\n");
        return 1;
    }

    age.year = today.year - dob.year;
    age.month = today.month - dob.month;
    age.day = today.day - dob.day;

    if (age.day < 0) {
        age.month--;
        int previousMonth = today.month - 1;
        int previousYear = today.year;

        if (previousMonth == 0) {
            previousMonth = 12;
            previousYear--;
        }

        age.day += daysInMonth(previousMonth, previousYear);
    }

    if (age.month < 0) {
        age.year--;
        age.month += 12;
    }

    printf("\nYour Age is:\n");
    printf("%d Years, %d Months, %d Days\n",
           age.year, age.month, age.day);

    return 0;
}
