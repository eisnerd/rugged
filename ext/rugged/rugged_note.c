/*
 * The MIT License
 *
 * Copyright (c) 2011 GitHub, Inc
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "rugged.h"

extern VALUE rb_mRugged;
extern VALUE rb_cRuggedObject;
extern VALUE rb_cRuggedRepo;

VALUE rb_cRuggedNote;

/*
 * Rugged Note
 */

void rb_git_note__free(git_note *note)
{
	if (note != NULL)
		git_note_free(note);
}

VALUE rugged_note_new(VALUE owner, git_note *note)
{
	if (note == NULL)
		return Qnil;

	VALUE rb_object, klass = rb_cRuggedNote;
	rb_object = Data_Wrap_Struct(klass, NULL, &rb_git_note__free, note);
        rugged_set_owner(rb_object, owner);
        return rb_object;

}

static VALUE rb_git_note_oid_GET(VALUE self)
{
        git_note *note;
        Data_Get_Struct(self, git_note, note);
        return rugged_create_oid(git_note_oid(note));
}

/*
 *	call-seq:
 *		note.message -> string
 *
 *	Return the note message
 *
 */
static VALUE rb_git_note_message_GET(VALUE self)
{
	git_note *note;
	Data_Get_Struct(self, git_note, note);
	return rugged_str_new2(git_note_message(note), NULL);
}

void Init_rugged_note()
{
	/*
	 * Note
	 */
	rb_cRuggedNote = rb_define_class_under(rb_mRugged, "Note", rb_cObject);

	rb_define_method(rb_cRuggedNote, "oid", rb_git_note_oid_GET, 0);
	rb_define_method(rb_cRuggedNote, "message", rb_git_note_message_GET, 0);
}
