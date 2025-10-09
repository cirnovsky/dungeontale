#ifndef DIALOG_H
#define DIALOG_H

typedef struct {
	int speaker;
	char *content;
} Dialog;

Dialog *dialog_create(int speaker, char *content);
int dialog_get_speaker(Dialog *dialog);
char *dialog_get_content(Dialog *dialog);
void dialog_destroy(Dialog *dialog);

#endif
