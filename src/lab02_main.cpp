#include <iostream>
#include <array_list.h>
#include <iomanip>
#include <person.h>



int main(int argc, char** argv)
{
    // The basic test program (for floats)
    ssuds::ArrayList<float> float_list;
    
    std::cout << "test1 (basics):\n=====\n";                        // test1 (basics):                       
    float_list.append(2.3f);                                        // ======
    float_list.append(2.6f);
    std::cout << "\tsize=" << float_list.size() << std::endl;       //     size=2
    std::cout << "\titem0=" << float_list.at(0) << std::endl;       //     item0=2.3
    std::cout << "\titem1=" << float_list.at(1) << std::endl;       //     item1=2.6
    float_list.at(0) -= 0.1f;
    float_list.at(1)++;
    std::cout << "\titem0=" << float_list.at(0) << std::endl;       //     item0=2.2
    std::cout << "\titem1=" << float_list.at(1) << std::endl;       //     item1=3.6

    std::cout << "\ntest2 (insert):\n=====\n";                      // test2 (insert):  
    float_list.insert(1.8f, 0);                                     // ======
    float_list.insert(4.2f, 3);                                     //     item0=1.8 
    float_list.insert(2.2f, 1);                                     //     item1=2.2
    for (unsigned int i = 0; i < float_list.size(); i++)            //     item2=2.2   
        std::cout << "\titem" << i << "=" << float_list.at(i) << "\n"; //     item3=3.6
                                                                    //     item4=4.2


    std::cout << "\ntest3 (grow):\n=====\n";                        // test3 (grow):
                                                                    // ======
    std::cout << "\tsize=" << float_list.size() << "\n";            //     size=5
    std::cout << "\tcapacity=" << float_list.capacity() << "\n";    //     capacity=5
    float_list.append(5.6f);   // <= a capacity increase should be triggered here
    float_list.append(2.2f);
    std::cout << "\tsize=" << float_list.size() << "\n";            //     size=7
    std::cout << "\tcapacity=" << float_list.capacity() << "\n";    //     capacity=10
                                            
    for (unsigned int i = 0; i < float_list.size(); i++)            //     item0=1.8              
        std::cout << "\titem" << i << "=" << float_list.at(i) << "\n"; //     item1=2.2   
                                                                    //     item2=2.2
                                                                    //     item3=3.6
                                                                    //     item4=4.2
                                                                    //     item5=5.6
                                                                    //     item6=2.2
    

    std::cout << "\ntest4 (stream):\n=====\n";                      // test4 (stream):
                                                                    // ======
    std::cout << "\t";
    float_list.output(std::cout);
    std::cout << std::endl;                                         //     [1.8, 2.2, 2.2, 3.6, 4.2, 5.6, 2.2]



    std::cout << "\ntest5 (find all):\n=====\n";                    // test5 (find all):
    int index = float_list.find(2.2f, 0);                           // =====
    while (index != -1)                                             //     Found occurrence of 2.2 at index 1
    {                                                               //     Found occurrence of 2.2 at index 2
        std::cout << "\tFound occurrence of 2.2 at index " << index << "\n"; 
        index++;            // Look at the next spot (or later)
        if (index == float_list.size())                             //     Found occurrence of 2.2 at index 6
            break;
        index = float_list.find(2.2f, index);
    }

    std::cout << "\ntest6 (remove_all [and remove]):\n=====\n";     // test6 (remove_all [and remove])
                                                                    // =====
    std::cout << "\tsize=" << float_list.size() << "\n";            //     size=7
    std::cout << "\tcapacity=" << float_list.capacity() << "\n";    //     capacity=10
    std::cout << "\tremoved " << float_list.remove_all(2.2f);                   // <= a capacity decrease should be triggered here
    std::cout << " items\n";                                        //     removed 3 items
    std::cout << "\t"; float_list.output(std::cout); std::cout << "\n"; //     [1.8, 3.6, 4.2, 5.6]
    std::cout << "\tsize=" << float_list.size() << "\n";            //     size=4
    std::cout << "\tcapacity=" << float_list.capacity() << "\n";    //     capacity=5
    
    
    std::cout << "\ntest 7 (reserve and Person's):\n=====\n";       // test7 (reserve and Person's)
    ssuds::ArrayList<example::Person> plist;                        // =====
    std::cout << "\tplist size=" << plist.size() << "\n";           //     plist size=0
    std::cout << "\tplist capacity=" << plist.capacity() << "\n";   //     plist capacity=5
    char temp_string[4] = { 0, 0, 0, 0 };
    plist.reserve(26);
    std::cout << "\tplist size=" << plist.size() << "\n";           //     plist size=0
    std::cout << "\tplist capacity=" << plist.capacity() << "\n";   //     plist capacity=26
    for (unsigned int i = 0; i < 26; i++)
    {
        temp_string[0] = 'A' + i;
        temp_string[1] = temp_string[2] = 'a' + i;
        std::string s(temp_string);
        example::Person p(s, "Smith", 100 + i, i + 0.5f);
        plist.append(p);
        plist.at(plist.size() - 1).set_hours_worked(i * 2);
    }
    plist.insert(example::Person("---", "###", 5000, 0.0f), 1);
    std::cout << "\tplist size=" << plist.size() << "\n";           //     plist size=26
    std::cout << "\tplist capacity=" << plist.capacity() << "\n";   //     plist capacity=26
    std::cout << std::setprecision(2) << std::fixed;
    for (unsigned int i = 0; i < plist.size(); i++)                 //     Aaa Smith $0.00
    {                                                               //     --- ### $0.00
        example::Person p = plist.at(i);                            //     Bbb Smith $3.00
        std::cout << "\t" << p.get_name(false) << " ";              //     Ccc Smith $10.00
        std::cout << " $" << p.get_salary() << "\n";                //     Ddd Smith $21.00 
    }                                                               //     Eee Smith $36.00      
                                                                    //     (more)
                                                                    //     Zzz Smith $1275.00

#
    return 0;
} 


