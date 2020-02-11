#ifndef ProgramState_hpp
#define ProgramState_hpp

class ProgramState //virtual functions
{
public:
	virtual void Initialization() = 0;
	virtual void Input() = 0;
	virtual void Updating(double deltaTime) = 0;
	virtual void Drawing(double deltaTime) = 0;
};

#endif
