#include "shell.h"

/** alloc_mem - Function to allocate memory with error handling
 * @size: parameter
 * Return: void
 */

void *alloc_mem(size_t size)
{
	void *ptr = malloc(size);
	if (ptr == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

/** realloc_mem -Function to reallocate memory with error handling
 * @ptr: pointer parameter
 * @size: size parameter
 * Return: void
 */

void *realloc_mem(void *ptr, size_t size)
{
	void *new = realloc(ptr, size);
	if (new == NULL && size != 0)
	{
		perror("Memory reallocation error");
		exit(EXIT_FAILURE);
	}
	return (new);
}

/** free_mem - Function to free allocated memory
 * @ptr: pointer parameter
 * Return: NULL
 */

void free_mem(void *ptr) {
	free(ptr);
}

/** refill_buf - Function to refill the buffer from the file
 * @buffer: buffer parameter
 * @p: position parameter
 * @size: size parameter
 * @stream: streamed file
 * Return: Null
 */

void refill_buf(char **buffer, size_t *p, size_t *size, FILE *stream)
{
	if (*p == *size)
	{
		size_t bytesRead = fread(*buffer, 1, *size, stream);
		if (bytesRead == 0 && ferror(stream))
		{
			perror("Error reading from file");
			exit(EXIT_FAILURE);
		}
		*size = bytesRead;
		*p = 0;
	}
}

/** write_to_line - Function to copy characters from the buffer to the line
 * @buffer: buffer parameter
 * @p: position parameter
 * @lineptr: line pointer
 * @n: size parameter
 * @i: --
 * Return: returns i
 */

size_t write_to_line(char buffer[], size_t *p, char **lineptr, size_t *n, size_t i)
{
	while (*p < *n && buffer[*p] != '\n')
	{
		if (i >= *n - 1)
		{
			*n *= 2;
			*lineptr = realloc_mem(*lineptr, *n);
		}
		(*lineptr)[i++] = buffer[(*p)++];
	}
	if (i < *n)
	{
		(*lineptr)[i] = '\0';
	}
	else
	{
		*lineptr = realloc_mem(*lineptr, *n + 1);
		(*lineptr)[i] = '\0';
	}
	return (i);
}
