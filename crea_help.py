helps = 'const char *help_string = ';

f = open('help.html', 'r')

h = ''
for line in f:
    h += '"' + line.strip() + ' "' + "\n"


f2 = open('help.h', 'w')

f2.write(helps+h+";")
