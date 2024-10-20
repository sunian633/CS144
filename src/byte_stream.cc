#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ), _written_size(0), _read_size(0),  _end_of_input(false),  _pipe(){}

bool Writer::is_closed() const
{
  // Your code here.
  return _end_of_input;
}

void Writer::push( string data )
{
  // Your code here.
  if(available_capacity() == 0)
    return;
  uint64_t _write_size = min(data.size(), capacity_ - _pipe.size());
  for(uint64_t i = 0; i < _write_size; i++)
    _pipe.push_back(data[i]);
  _written_size += _write_size;
  (void)data;
}

void Writer::close()
{
  // Your code here.
  _end_of_input = true;
  return;
}

uint64_t Writer::available_capacity() const
{
  // Your code here.
  return capacity_ - _pipe.size();
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return _written_size;
}

bool Reader::is_finished() const
{
  // Your code here.
  return _end_of_input == true && bytes_buffered() == 0;
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return _read_size;
}

string_view Reader::peek() const
{
  // Your code here.
  if(_pipe.empty())
    return string_view();
  return string_view(&_pipe[0], _pipe.size());
}

void Reader::pop( uint64_t len )
{
  // Your code here.
  uint64_t _read_len = min(len, _pipe.size());
  _pipe.erase(_pipe.begin(), _pipe.begin() + _read_len);
  _read_size += _read_len;
  (void)len;
}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  return _pipe.size();
}
