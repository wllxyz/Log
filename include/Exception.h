#ifndef EXCEPTION_H
#define EXCEPTION_H

class Exception
{
public:
	Exception(const std::string& type = "Exception", const std::string& msg = ""):type(type),message(msg){}
	const std::string& GetType() { return type; }
	const std::string& GetMessage() { return message; }
	std::string ToString() const { return (type + ":" + message); }
private:
	std::string type;
	std::string message;
};

inline std::ostream& operator<< (std::ostream& o, const Exception& e)
{
        return o<<e.ToString();
}


#endif

