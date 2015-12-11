#ifndef GLDBG_H
#define GLDBG_H

#include <GL/glew.h>
#include "dbg.h"

#define glCheckError(message) ___glCheckError(message,BASE_FILE,__LINE__)
static inline void ___glCheckError(const char * message, const char * filename, int line)
{
	int i=0;
	GLenum err = glGetError();
	while(err!=GL_NO_ERROR) {

		switch(err) {
			case GL_INVALID_OPERATION:
				fprintf(stderr, ERROR_TEXT "[GL ERROR %d] %s:%d %s : GL_INVALID_OPERATION\n",i++, filename , line ,message); break;
			case GL_INVALID_ENUM:
				fprintf(stderr, ERROR_TEXT "[GL ERROR %d] %s:%d %s : GL_INVALID_ENUM\n",i++, filename , line ,message); break;
			case GL_INVALID_VALUE:
				fprintf(stderr, ERROR_TEXT "[GL ERROR %d] %s:%d %s : GL_INVALID_VALUE\n",i++, filename , line ,message); break;
			case GL_OUT_OF_MEMORY:
				fprintf(stderr, ERROR_TEXT "[GL ERROR %d] %s:%d %s : GL_OUT_OF_MEMORY\n",i++, filename , line ,message); break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				log_err("[GL ERROR %d] %s : GL_INVALID_FRAMEBUFFER_OPERATION",i++,message); break;
				fprintf(stderr, ERROR_TEXT "[GL ERROR %d] %s:%d %s : GL_INVALID_FRAMEBUFFER_OPERATION\n",i++, BASE_FILE, __LINE__,message); break;
		}
		err = glGetError();
	}
}
#endif
