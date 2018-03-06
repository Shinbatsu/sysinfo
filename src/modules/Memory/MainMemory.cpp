#include "MainMemory.hpp"

MainMemory::MainMemory(void) : _name("Memory"), _min(0.0f), _max(100.0f), _graphs(std::map< std::string, std::deque<float> >()), _data(std::map<std::string, std::string>()), _frame(0)
{
    this->update();
}

MainMemory::MainMemory(MainMemory const &src)
{
    *this = src;
}

MainMemory::~MainMemory() {}

void MainMemory::dequeUpdate(std::string name, float ret)
{
    if (!this->_graphs[name].empty())
    {
        while (this->_graphs[name].size() > DEQUE_SIZE)
            this->_graphs[name].pop_back();
        this->_graphs[name].push_front(ret);
    }
    else
        this->_graphs[name] = std::deque<float>(DEQUE_SIZE, 0);
}

double MainMemory::parseMemValue(const char * b)
{
    while((*b) && (isdigit(*b) == false))
        b++;
    return isdigit(*b) ? atof(b) : -1.0;
}

float MainMemory::getSystemMemoryUsagePercentage()
{
    FILE * fpIn = popen("/usr/bin/vm_stat", "r");
    if (!fpIn)
        throw std::runtime_error("memory module error: open on /usr/bin/vmstat failed");

    double pagesUsed = 0.0, totalPages = 0.0;
    char buf[512];
    while(fgets(buf, sizeof(buf), fpIn) != NULL)
    {
        if (strncmp(buf, "Pages", 5) == 0)
        {
            double val = parseMemValue(buf);
            if (val >= 0.0)
                if ((strncmp(buf, "Pages wired", 11) == 0)||(strncmp(buf, "Pages active", 12) == 0)) pagesUsed += val;
                    totalPages += val;
        }
        else if (strncmp(buf, "Mach Virtual Memory Statistics", 30) != 0)
            break;  // Stop at "Translation Faults"
    }
    pclose(fpIn);

    if (totalPages > 0.0){
        float tmp = static_cast<float>(pagesUsed / totalPages);
        // std::cout << "memory " << tmp << std::endl;  
        return tmp * 100;
    }
    return 0.0f;
}

void MainMemory::update(void)
{
	try
	{
		this->dequeUpdate("Memory usage (%)", this->getSystemMemoryUsagePercentage());
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		exit(0);
	}
}

const float &MainMemory::getGraphMin(void) const
{
    return this->_min;
}

const float &MainMemory::getGraphMax(void) const
{
    return this->_max;
}

const std::map< std::string, std::deque<float> > &MainMemory::getGraphs(void) const
{
    return this->_graphs;
}

const std::map<std::string, std::string> &MainMemory::getData(void) const
{
    return this->_data;
}

const std::string &MainMemory::getName(void) const
{
    return this->_name;
}

void MainMemory::setName(std::string name)
{
    this->_name = name;
}

MainMemory &MainMemory::operator=(MainMemory const &rhs)
{
    this->_name = rhs.getName();
    this->_graphs = rhs.getGraphs();
    this->_data = rhs.getData();
    this->_min = rhs.getGraphMin();
    this->_max = rhs.getGraphMax();
    this->_frame = rhs._frame;
return *this;
}
