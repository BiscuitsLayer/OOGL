/*
	Copyright (C) 2023 Sergey Vinogradov

	Permission is hereby granted, free of charge, to any person obtaining a copy of
	this software and associated documentation files (the "Software"), to deal in
	the Software without restriction, including without limitation the rights to
	use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
	the Software, and to permit persons to whom the Software is furnished to do so,
	subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
	FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
	COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
	IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
	CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
*/

#include <GL/GL/StorageBuffer.hpp>
#include <vector>

namespace GL
{
	StorageBuffer::StorageBuffer()
	{
		gc.Create( obj, glGenBuffers, glDeleteBuffers );
	}

	StorageBuffer::StorageBuffer( const StorageBuffer& other )
	{
		gc.Copy( other.obj, obj );
	}

	StorageBuffer::StorageBuffer( const void* data, size_t length, BufferUsage::buffer_usage_t usage, int index )
	{
		gc.Create( obj, glGenBuffers, glDeleteBuffers );
		Data( data, length, usage, index );
	}

	StorageBuffer::~StorageBuffer()
	{
		gc.Destroy( obj );
	}

	StorageBuffer::operator GLuint() const
	{
		return obj;
	}

	const StorageBuffer& StorageBuffer::operator=( const StorageBuffer& other )
	{
		gc.Copy( other.obj, obj, true );
		return *this;
	}

	void StorageBuffer::Data( const void* data, size_t length, BufferUsage::buffer_usage_t usage, int index )
	{
		glBindBuffer( GL_SHADER_STORAGE_BUFFER, obj );
		glBufferData( GL_SHADER_STORAGE_BUFFER, length, data, usage );
		glBindBufferBase( GL_SHADER_STORAGE_BUFFER, index, obj );
	}

	void StorageBuffer::SubData( const void* data, size_t offset, size_t length )
	{
		glBindBuffer( GL_SHADER_STORAGE_BUFFER, obj );
		glBufferSubData( GL_SHADER_STORAGE_BUFFER, offset, length, data );
	}

	void StorageBuffer::GetSubData( void* data, size_t offset, size_t length )
	{
		glBindBuffer( GL_SHADER_STORAGE_BUFFER, obj );
		glGetBufferSubData( GL_SHADER_STORAGE_BUFFER, offset, length, data );
	}

	GC StorageBuffer::gc;
}