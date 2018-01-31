#ifndef OB_WIDTHSTREAM_HH
#define OB_WIDTHSTREAM_HH

// usage
// OB::Widthstream out{<width-size>, std::cout};
// out.indent(<indent-size>) << "string here";

#include <iostream>
#include <streambuf>
#include <iomanip>

namespace OB
{
class Widthbuf: public std::streambuf
{
public:
  Widthbuf(size_t w, std::streambuf* s):
    indent_width {0},
    def_width {w},
    width {w},
    sbuf {s},
    count {0}
  {
  }

  ~Widthbuf()
  {
    overflow('\n');
  }

  void set_indent(size_t w)
  {
    if (w == 0)
    {
      prefix.clear();
      indent_width = 0;
      width = def_width;
    }
    else
    {
      indent_width += w;
      prefix = std::string(indent_width, ' ');
      width -= w;
    }
  }

private:
  using string = std::basic_string<char_type>;

  int_type overflow(int_type c)
  {
    if (traits_type::eq_int_type(traits_type::eof(), c))
    {
      return traits_type::not_eof(c);
    }

    switch (c)
    {
      case '\n':
      case '\r':
      {
        buffer += c;
        count = 0;
        sbuf->sputn(prefix.c_str(), static_cast<std::streamsize>(indent_width));
        int_type rc = sbuf->sputn(buffer.c_str(), static_cast<std::streamsize>(buffer.size()));
        buffer.clear();
        return rc;
      }
      case '\a':
        return sbuf->sputc(c);
      case '\t':
        buffer += c;
        count += tab_width - count % tab_width;
        return c;
      default:
        if (count >= width)
        {
          size_t wpos = buffer.find_last_of(" \t");
          if (wpos != string::npos)
          {
            sbuf->sputn(prefix.c_str(), static_cast<std::streamsize>(indent_width));
            sbuf->sputn(buffer.c_str(), static_cast<std::streamsize>(wpos));
            count = buffer.size()-wpos-1;
            buffer = string(buffer, wpos+1);
          }
          else
          {
            sbuf->sputn(prefix.c_str(), static_cast<std::streamsize>(indent_width));
            sbuf->sputn(buffer.c_str(), static_cast<std::streamsize>(buffer.size()));
            buffer.clear();
            count = 0;
          }
          sbuf->sputc('\n');
        }
        buffer += c;
        ++count;
        return c;
    }
  }

  size_t indent_width;
  size_t def_width;
  size_t width;
  std::streambuf* sbuf;
  size_t count;
  size_t tab_count;
  static const int tab_width {4};
  std::string prefix;
  string buffer;
}; // class widthbuf

class Widthstream : public std::ostream
{
public:
  Widthstream(size_t width, std::ostream &os):
    std::ostream {&buf},
    buf {width, os.rdbuf()}
  {
  }

  Widthstream& indent(size_t w)
  {
    buf.set_indent(w);
    return *this;
  }

private:
  Widthbuf buf;
}; // class Widthstream
} // namespace OB
#endif // OB_WIDTHSTREAM_HH
