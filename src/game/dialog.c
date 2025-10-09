#include "game/dialog.h"
#include <stdlib.h>
#include <assert.h>

Dialog *dialog_create(int speaker, char *content) {
	Dialog *result = malloc(sizeof(Dialog));

	result->speaker = speaker;
	result->content = content;

	return result;
}

int dialog_get_speaker(Dialog *dialog) {
	assert(dialog != NULL);

	return dialog->speaker;
}

char *dialog_get_content(Dialog *dialog) {
	assert(dialog != NULL);

	return dialog->content;
}

void dialog_destroy(Dialog *dialog) {
	assert(dialog != NULL);

	free(dialog);
}
