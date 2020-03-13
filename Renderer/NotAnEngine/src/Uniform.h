class Uniform
{
public:
	const static int nameBufferSize = 32;

	Uniform(const char* name, unsigned int type, void* value);

private:
	const char* _name;
	unsigned int _type;
	void* _value;

	friend class Shader;
	friend class Material;
};