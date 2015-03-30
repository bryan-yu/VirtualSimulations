#pragma once

#ifndef EMOTIONS_H
#define EMOTIONS_H

typedef struct 
{
	std::string name;
	float value;

	float R;
	float G;
	float B;
	float A;
}Emotion;

class Emotions
{
public:
	Emotions(){};
	~Emotions(){};

protected:

private:
	//hash table...
};

#endif