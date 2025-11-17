#ifndef FILEMANAGER_HH
#define FILEMANAGER_HH
#include <filesystem>
#include <fstream>
#include <unordered_map>

#include "University.hh"
#include "Faculty.hh"
#include "Student.hh"

using namespace std;

// abstraction for storage
class IUniversityStorage {
public:
    virtual ~IUniversityStorage() = default;

    // Save the whole university somewhere (dir is e.g. "data")
    virtual void save(const manageUniversity& uni,
                      const std::string& dir) = 0;

    // Load a university with a given name from somewhere
    virtual manageUniversity load(const std::string& dir,
                                  const std::string& universityName) = 0;
};

// ---------- main API ----------
class FileManager : public IUniversityStorage{
public:
    // Saves to: data/faculties.txt and data/members.txt
    // faculties.txt:   name|abbr|field
    // members.txt:     abbr|E|<studentLine>  or  abbr|G|<studentLine>
    void save(const manageUniversity& uni, const string& dir = "data") override {
        namespace fs = std::filesystem;
        fs::create_directories(dir);

        const auto& facs = uni.getFaculties();

        // 1) faculties
        {
            ofstream out(dir + "/faculties.txt");
            for (const auto& f : facs) {
                out << f.getName() << '|'
                    << f.getAbbreviation() << '|'
                    << fieldToString(f.getStudyField()) << '\n';
            }
        }
        // 2) membership
        {
            ofstream out(dir + "/members.txt");
            for (const auto& f : facs) {
                for (const auto& s : f.getStudents()) {
                    out << f.getAbbreviation() << "|E|" << studentToLine(s) << '\n';
                }
                for (const auto& g : f.getGraduates()) {
                    out << f.getAbbreviation() << "|G|" << studentToLine(g) << '\n';
                }
            }
        }
    }

    // Rebuilds a manageUniversity from files.
    // If files are missing/empty, returns an empty university with the given name.
    manageUniversity load(const string& dir = "data",
                                 const string& universityName = "TUM") override
    {
        namespace fs = std::filesystem;
        vector<Faculty> result;

        // Read base faculty rows (name|abbr|field)
        struct FacMeta { string name; string abbr; StudyField field; };
        vector<FacMeta> metas;

        if (fs::exists(dir + "/faculties.txt")) {
            ifstream in(dir + "/faculties.txt");
            string line;
            while (getline(in, line)) {
                if (line.empty()) continue;
                auto p = split(line, '|');
                if (p.size()!=3) continue;
                metas.push_back(FacMeta{ p[0], p[1], fieldFromString(p[2]) });
            }
        }

        // Prepare buckets for enrolled/graduated per abbr
        unordered_map<string, vector<Student>> enrolled, grads;

        if (fs::exists(dir + "/members.txt")) {
            ifstream in(dir + "/members.txt");
            string line;
            while (getline(in, line)) {
                if (line.empty()) continue;
                // abbr|E|first|last|email|eD|eM|eY|bD|bM|bY
                auto p = split(line, '|');
                if (p.size()!=12) continue; // abbr, E/G, + 9 student fields
                string abbr = p[0];
                char kind = p[1].empty() ? 'E' : p[1][0];
                vector<string> sp(p.begin()+2, p.end());
                Student s = studentFromParts(sp);
                if (kind=='G') grads[abbr].push_back(s);
                else           enrolled[abbr].push_back(s);
            }
        }

        // Build Faculty objects with ctor that accepts students + graduates
        for (const auto& m : metas) {
            auto es = enrolled.count(m.abbr) ? enrolled[m.abbr] : vector<Student>{};
            auto gs = grads.count(m.abbr)    ? grads[m.abbr]    : vector<Student>{};
            result.emplace_back(m.name, m.abbr, std::move(es), std::move(gs), m.field);
        }

        // manageUniversity has a ctor (name, vector<Faculty>)
        return manageUniversity(universityName, std::move(result));
    }
};

#endif //FILEMANAGER_HH
