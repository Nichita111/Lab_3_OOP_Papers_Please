#ifndef DISPLAY_HH
#define DISPLAY_HH
#include <iostream>
#include <string>

using namespace std;

class Task_1{
private:
    int width;
    int height;
    float ppi;
    string model;

public:

    Task_1(int width, int height, float ppi, string model)
    {
        this->width = width;
        this->height = height;
        this->ppi = ppi;
        this->model = model;
    }

    void setWidth(int w) {
        width = w;
    }

    auto getWidth() const {
        return width;
    }

    void setHeight(int h) {
        height = h;
    }

    auto getHeight() const {
        return height;
    }

    void setPPI(float p){
        ppi = p;
    }

    auto getPPI() const {
        return ppi;
    }

    void setModel(string &m) {
        model = m;
    }

    auto getModel() const {
        return model;
    }

    void compareSize(Task_1 m) const
    {
        auto size_of_a = width*height;
        auto size_of_b = m.width*m.height;
        if (size_of_a == size_of_b) {
            cout << m.model << " and " << model << " have same size\n";
        }
        else if (size_of_a > size_of_b) {
            cout << "The "<< model << " display is bigger than "<< m.model <<" and is equal to = " << size_of_a <<"\n";
        } else {
            cout << "The "<< m.model <<" display is bigger than "<< model <<" and is equal to = " << size_of_b <<"\n";
        }
    }

    void compareSharpness(Task_1 m) const
    {
        auto epsilon = 0.00001;
        auto sharpness_of_a = ppi;
        auto sharpness_of_b = m.ppi;
        if (sharpness_of_a - epsilon <= sharpness_of_b and sharpness_of_a + epsilon >= sharpness_of_b) {
            cout << m.model << " and " << model << " have same sharpness\n";
        }
        else if (sharpness_of_a > sharpness_of_b) {
            cout << "The "<< model << " display is sharper than "<< m.model <<" and is equal to = " << sharpness_of_a <<"\n";
        } else {
            cout << "The "<< m.model <<" display is sharper than "<< model <<" and is equal to = " << sharpness_of_b <<"\n";
        }
    }

    void  compareWithMonitor(Task_1 m) const {
        compareSize(m);
        compareSharpness(m);
    }

};

#endif //DISPLAY_HH
