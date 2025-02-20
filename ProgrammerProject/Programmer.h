/*
 `....
`..   `..   `..      `..
`..         `..      `..
`..     `...`.....`...`.....
`..         `..      `..
`..   `..   `..      `..
 `....

Michelle Lynch
*/

#ifndef PROGRAMMER_H
#define PROGRAMMER_H

#include <iostream>		// ostream
#include <string>		// string
#include <vector>		// vector

#define VERBOSE 1

class Programmer {
public:
	Programmer(); //default constructor
	Programmer(std::string); //1-arg constructor
	Programmer(const Programmer&); //copy constructor
	Programmer(std::string, std::vector<std::string>); //All arg constructor
	~Programmer();

	void SetName(const std::string&);
	std::string GetName() const { return name_; }
	void SetLanguages(const std::vector<std::string&>);
	std::vector<std::string> GetLanguages() const { return languages_; };
	static int GetCount() { return programmer_count_; }

	friend std::ostream& operator<<(std::ostream& output, const Programmer& p);

private:
	std::string name_;
	std::vector<std::string> languages_;

	static int programmer_count_;
};

#endif
