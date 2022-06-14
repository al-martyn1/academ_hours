#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <utility>
#include <vector>
#include <algorithm>
#include <map>





//-----------------------------------------------------------------------------
//! Возвращает true для букв латиницы в нижнем регистре
inline bool is_alpha_lower( char ch )
{
    if (ch>='a' && ch<='z')
        return true;
    return false;
}

//! Возвращает true для букв латиницы в верхнем регистре
inline bool is_alpha_upper( char ch )
{
    if (ch>='A' && ch<='Z')
        return true;
    return false;
}

//! Возвращает true для цифровых символов ASCII
inline bool is_digit( char ch )
{
    if (ch>='0' && ch<='9')
        return true;
    return false;
}

//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
//! Возвращает true для букв латиницы в нижнем регистре
inline bool is_alpha_lower( uint8_t ch ) { return is_alpha_lower( (char)ch ); }
//! Возвращает true для букв латиницы в верхнем регистре
inline bool is_alpha_upper( uint8_t ch ) { return is_alpha_upper( (char)ch ); }
//! Возвращает true для цифровых символов ASCII
inline bool is_digit      ( uint8_t ch ) { return is_digit      ( (char)ch ); }

//! Возвращает true для букв латиницы в нижнем регистре
inline bool is_alpha_lower( wchar_t ch ) { return is_alpha_lower( (char)ch ); }
//! Возвращает true для букв латиницы в верхнем регистре
inline bool is_alpha_upper( wchar_t ch ) { return is_alpha_upper( (char)ch ); }
//! Возвращает true для цифровых символов ASCII
inline bool is_digit      ( wchar_t ch ) { return is_digit      ( (char)ch ); }

//! Возвращает true для букв латиницы
inline bool is_alpha      ( char ch )    { return is_alpha_lower(ch) || is_alpha_upper(ch); }
//! Возвращает true для букв латиницы
inline bool is_alpha      ( uint8_t ch ) { return is_alpha_lower(ch) || is_alpha_upper(ch); }
//! Возвращает true для букв латиницы
inline bool is_alpha      ( wchar_t ch ) { return is_alpha_lower(ch) || is_alpha_upper(ch); }

//! Возвращает true для символа пробела (и только для него)
inline bool is_space      ( char ch )    { return ch==' '; }
//! Возвращает true для символа пробела (и только для него)
inline bool is_space      ( uint8_t ch ) { return ch==(uint8_t)' '; }
//! Возвращает true для символа пробела (и только для него)
inline bool is_space      ( wchar_t ch ) { return ch==L' '; }

//! Возвращает true для символа пробела или таба
inline bool is_space_ot_tab( char ch )    { return ch==' ' || ch=='\t'; }
//! Возвращает true для символа пробела или таба
inline bool is_space_ot_tab( uint8_t ch ) { return is_space_ot_tab((char)ch); }
//! Возвращает true для символа пробела или таба
inline bool is_space_ot_tab( wchar_t ch ) { return is_space_ot_tab((char)ch); }

//! Возвращает true для символа пробела, таба ли какого-либо из символов перевода строки
inline bool is_whitespace ( char ch )    { return ch==' ' || ch=='\r' || ch=='\n' || ch=='\t' || ch=='\v'; }
//! Возвращает true для символа пробела, таба ли какого-либо из символов перевода строки
inline bool is_whitespace ( uint8_t ch ) { return is_whitespace((char)ch); }
//! Возвращает true для символа пробела, таба ли какого-либо из символов перевода строки
inline bool is_whitespace ( wchar_t ch ) { return is_whitespace((char)ch); }

//! Возвращает true для какого-либо из символов перевода строки
inline bool is_linefeed ( char ch )    { return ch=='\r' || ch=='\n'; }
//! Возвращает true для какого-либо из символов перевода строки
inline bool is_linefeed ( uint8_t ch ) { return is_linefeed((char)ch); }
//! Возвращает true для какого-либо из символов перевода строки
inline bool is_linefeed ( wchar_t ch ) { return is_linefeed((char)ch); }

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//! Возвращает отрицание функционального объекта-предиката
/*! 
    \tparam ActualPred Тип предиката
    \tparam ParamType  Тип аргумента предиката
    \return Отрицание предиката
 */

template<typename ActualPred, typename ParamType>
struct not_pred
{
    const ActualPred &actualPred; //!< Ссылка на предикат для отрицания его результата
    //! Конструктор предиката отрицания
    not_pred( const ActualPred &a /*!< предикат для отрицания */ ) : actualPred(a) {}
    //! Оператор функционального объекта
    bool operator()( ParamType ch ) const { return !actualPred(ch); }
};

//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
//! Возвращает true, если аргумент - пробел
template<typename CharType>
struct space_pred
{
    //! Оператор функционального объекта
    bool operator()( CharType  ch ) const { return is_space(ch); }
};

//-----------------------------------------------------------------------------
//! Возвращает true, если аргумент - пробел или таб
template<typename CharType>
struct space_or_tab_pred
{
    //! Оператор функционального объекта
    bool operator()( CharType ch )  const { return is_space_ot_tab(ch); }
};

//-----------------------------------------------------------------------------
//! Возвращает true, если аргумент - пробел, таб, втаб, или перевод строки
template<typename CharType>
struct whitespace_pred
{
    //! Оператор функционального объекта
    bool operator()( CharType ch )  const { return is_whitespace(ch); }
};

//-----------------------------------------------------------------------------
//! Возвращает true, если аргумент - перевод строки
template<typename CharType>
struct linefeed_pred
{
    //! Оператор функционального объекта
    bool operator()( CharType ch )  const { return is_linefeed(ch); }
};

//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
template <typename StringType, typename TrimPred> inline void ltrim( StringType &s, const TrimPred &pred )
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), not_pred<TrimPred, typename StringType::value_type>(pred) ));
}

//-----------------------------------------------------------------------------
//! Правый inplace trim с предикатом
/*! \copydetails ltrim */
template <typename StringType, typename TrimPred > inline void rtrim(StringType &s, const TrimPred &pred)
{
    s.erase( std::find_if(s.rbegin(), s.rend(), not_pred<TrimPred,typename StringType::value_type>(pred) ).base(), s.end());
}

//-----------------------------------------------------------------------------
//! Двусторонний inplace trim с предикатом
/*! \copydetails ltrim */
template <typename StringType, typename TrimPred> inline void trim(StringType &s, const TrimPred &pred)
{
    ltrim(s,pred); rtrim(s,pred);
}







/*
int main(int argc, char* argv[])
{
    std::string str = "  rrr ";
    trim( str, space_pred<char>() );
    std::cout << str << "\n";
}
*/


template <typename StringType> inline bool split2pair(StringType str, StringType &f, StringType &s, typename StringType::size_type ch )
{
    typename StringType::size_type pos = str.find(ch);
    if (pos==str.npos)
    {
        f = str;
        return false;
    }

    f = StringType(str, 0, pos);
    s = StringType(str, pos+1);

    return true;
}

/*
int main(int argc, char* argv[])
{
    std::string str = "14:55";
    std::string hh,mm;
    split2pair(str, hh, mm, ':');

    std::cout << "Src: [" << str << "], HH: [" << hh << "], mm: [" << mm << "]\n";
}
*/


// return minutes from 00:00
inline
int parseTimeFromHoursMinutes(const std::string &timeStr)
{
    std::string hh, mm;
    if (!split2pair(timeStr, hh, mm, ':'))
    {
        throw std::runtime_error( "Invalid time: " + timeStr);
    }

    trim( hh , space_pred<char>() );
    trim( mm , space_pred<char>() );

    int ihh = std::stoi( hh );
    int imm = std::stoi( mm );

    if (ihh<0 || ihh>23)
        throw std::runtime_error( "Invalid time (hours): " + timeStr);

    if (imm<0 || imm>59)
        throw std::runtime_error( "Invalid time (minutes): " + timeStr);

    return ihh*60+imm;
}

// return minutes start/end from 00:00
inline
std::pair<int,int> parseTimeInterval(const std::string intervalStr)
{
    std::string startTime, endTime;

    bool splitRes = split2pair(intervalStr, startTime, endTime, '-');

    int intStartTime = parseTimeFromHoursMinutes(startTime);

    if (!splitRes)
    {
        return std::make_pair(intStartTime, intStartTime+45);
    }
    else
    {
        return std::make_pair(intStartTime, parseTimeFromHoursMinutes(endTime));
    }

}

// In minutes
inline
int timeIntervalLen( std::pair<int,int> i)
{
    int res = i.first - i.second;
    return (res<0 ? -res : res); // + 1;
}

inline
std::string format2i( int i )
{
    std::stringstream oss;
    oss << std::setw(2) << std::setfill('0');
    oss<<i;
    return oss.str();
}

inline
std::string formatMinutesToHours( int minutes, int hourSize = 60 )
{
    return format2i(minutes/hourSize) + ":" + format2i(minutes%hourSize);
}

inline
std::string formatTimeInterval( std::pair<int,int>  timeInterval )
{
    return formatMinutesToHours(timeInterval.first) + "-" + formatMinutesToHours(timeInterval.second);
}


struct PairDetails
{
    int                 duration; // 
    int                 durationWithBreak; // с учетом перерыва внутри пары, если есть
    std::pair<int,int>  timeInterval;

};

inline
int calcAcademicMinutesCount( std::pair<int,int> timeInterval
                            , int bbp     // break between a pairs  - перерыв между парами
                            , int bwp     // break within a pairs   - перерыв внутри пары - может не быть - 0
                            , int hrlen   // academic hour lenght   - длительность академического часа, 45 минут по умолчанию
                            , std::vector< PairDetails > &pairsSched
                            )
{

    int tiLen = timeIntervalLen( timeInterval );
    int startTime = timeInterval.first;
    int academicMinutesTotal = 0;
    int minutesTotalOffset   = 0;

    while(tiLen>0)
    {
        if (academicMinutesTotal) // это уже не первая пара, нужно отнять перерыв между парами
        {
            if (tiLen<=bbp) // Остаток меньше перерыва между парами - вообще, ситуация странная
            {
                //std::cerr<<"1\n";
                return academicMinutesTotal;
            }

            tiLen -= bbp; // Отняли перерыв между парами
            minutesTotalOffset += bbp;
        }

        int pairStartTime = startTime + minutesTotalOffset;

        // Первый час пары
        if (tiLen<=hrlen) // если времени хватает только на первый час пары или его часть
        {
            //academicMinutesTotal += tiLen;
            pairsSched.push_back( PairDetails{ tiLen, tiLen, std::make_pair(pairStartTime, pairStartTime+tiLen) });
            //std::cerr<<"2\n";
            return academicMinutesTotal+tiLen;
        }


        // Первый час пары закрыли
        tiLen                -= hrlen;
        academicMinutesTotal += hrlen;
        minutesTotalOffset   += hrlen;


        // Перерыв внутри пары
        if (bwp)
        {
            if (tiLen<=bwp) // времени не хватает даже на перерыв между часами пары
            {
                // первый час целиком закрыт
                pairsSched.push_back( PairDetails{ hrlen, tiLen, std::make_pair(pairStartTime, pairStartTime+hrlen) });
                //std::cerr<<"3\n";
                return academicMinutesTotal;
            }
        
            tiLen -= bwp;
            minutesTotalOffset   += bwp;
        }

        // Второй час пары
        if (tiLen<=hrlen) // если времени хватает только на второй час пары или его часть
        {
            academicMinutesTotal += tiLen;
            minutesTotalOffset   += tiLen;
            auto acLen = startTime+minutesTotalOffset-pairStartTime;
            pairsSched.push_back( PairDetails{ acLen, acLen+bwp, std::make_pair(pairStartTime, startTime+minutesTotalOffset) });
            //std::cerr<<"4\n";
            return academicMinutesTotal;
        }

        // Второй час пары закрыли
        tiLen                -= hrlen;
        academicMinutesTotal += hrlen;
        minutesTotalOffset   += hrlen;
        pairsSched.push_back( PairDetails{ 2*hrlen, 2*hrlen+bwp, std::make_pair(pairStartTime, startTime+minutesTotalOffset) });

    }

    return academicMinutesTotal;
}


inline
void printSched( const std::vector< PairDetails > &pairsSched
               , const std::string &sep
               , bool  printNumber = false
               , bool  printDuration = false
               )
{
    int n = 1;
    for( const auto &pd : pairsSched)
    {
        if (n!=1)
        {
            std::cout << sep;
        }

        if (printNumber)
            std::cout << n << ": ";

        std::cout << formatTimeInterval(pd.timeInterval);

        if (printDuration)
        {
            std::cout << "  " << formatMinutesToHours(pd.duration);
            if (pd.durationWithBreak!=pd.duration)
                std::cout << " (" << formatMinutesToHours(pd.durationWithBreak) << ")";
        
        }
        
        // std::cout << "\n";
        ++n;
    }
}

/*
int main(int argc, char* argv[])
{
    int bbp     = 15; // break between a pairs  - перерыв между парами
    int bwp     =  5; // break within a pairs   - перерыв внутри пары - может не быть - 0
    int hrlen   = 45; // academic hour lenght   - длительность академического часа, 45 минут по умолчанию

    std::pair<int,int> timeInterval = parseTimeInterval("10:00-15:00");

    

    std::cout << "From: " << formatMinutesToHours(timeInterval.first)   << "\n";
    std::cout << "To  : " << formatMinutesToHours(timeInterval.second)  << "\n";


    std::cout << "\n";
    std::cout << "Schedule: (5 min break)\n";

    {
        std::vector< PairDetails > pairsSched;
        int totalAcMinutes = calcAcademicMinutesCount( timeInterval
                                                     , bbp   
                                                     , 5
                                                     , hrlen 
                                                     , pairsSched
                                                     );
       
        printSched( pairsSched, "\n", true, true );
        std::cout << "\n";
        printSched( pairsSched, ", ", false, false );
       
        std::cout << "\nTotal academic hours: " << formatMinutesToHours(totalAcMinutes, 45) << "\n";
    }

    std::cout << "\n";
    std::cout << "Schedule: (no break)\n";

    {
        std::vector< PairDetails > pairsSched;
        pairsSched.clear();
        int totalAcMinutes = calcAcademicMinutesCount( timeInterval
                                                     , bbp   
                                                     , 0
                                                     , hrlen 
                                                     , pairsSched
                                                     );
       
        printSched( pairsSched, "\n", true, true );
        std::cout << "\n";
        printSched( pairsSched, ", ", false, false );
       
        std::cout << "\nTotal academic hours: " << formatMinutesToHours(totalAcMinutes, 45) << "\n";
    }
    std::cout << "\n";

}
*/



int main(int argc, char* argv[])
{
    // academ_hours [BBC [BWC [HRLEN]]]
    // BBP    - break between a pairs    - 15 min default
    // BWP    - break within a pairs     - 0 min default
    // HRLEN  - (academic) hour lenght   - 45 min default

    int bbp    = 15; // min
    int bwp    = 0 ; // min
    int hrlen  = 45; // min

    if (argc>1) // BBP taken
    {
        bbp = std::stoi( std::string(argv[1]) );
    }

    if (argc>2) // BWP taken
    {
        bwp = std::stoi( std::string(argv[2]) );
    }

    if (argc>3) // HRLEN taken
    {
        hrlen = std::stoi( std::string(argv[3]) );
    }


    using std::cin;
    using std::cout;
    using std::cerr;
    using std::getline;

    // cout << "# Academic hour lenght: " << hrlen << ", break between pairs: " << bbp << ", break within a pairs: " << bwp << "\n";


    // #define DETAILED_OUT

    int totalAcMinutes = 0;
    int weekAcMinutes  = 0;

    std::map<std::string, int> acMinutesByDiscipline;

    try
    {
        std::string inputLine;
        while(getline(cin, inputLine))
        {
            trim( inputLine, space_pred<char>() );
       
            if (inputLine.empty() || inputLine[0]=='#' || inputLine[0]==';')
            {
                if (inputLine=="#$subtotal")
                {
                    std::cout << "Total academic hours: " << formatMinutesToHours(totalAcMinutes, 45) << "\n";
                }
                else if (inputLine=="#$endweek")
                {
                    std::cout << "Week academic hours: " << formatMinutesToHours(weekAcMinutes, 45) << "\n";
                    weekAcMinutes = 0;
                }
                else
                {
                    cout << inputLine << "\n";
                }
                
                #ifdef DETAILED_OUT
                    cout << "\n";
                #endif
                continue;
            }
       
            #ifdef DETAILED_OUT
                cout << "Input: " << inputLine << "\n";
            #endif
       
            // 16.05 11:00-13:00 Регистрация к. 126.1
       
            std::string dtStr, lectionsTimeStr, lectionsCommentStr;
       
            if (!split2pair(inputLine, dtStr, lectionsTimeStr, ' '))
            {
                throw std::runtime_error("Fatal error while parsing input line (1)");
                //cerr << "Fatal error";
                //return 1;
            }
       
            trim( dtStr           , space_pred<char>() );
            trim( lectionsTimeStr , space_pred<char>() );

            split2pair(lectionsTimeStr, lectionsTimeStr, lectionsCommentStr, ' ');
            trim( lectionsTimeStr     , space_pred<char>() );
            trim( lectionsCommentStr  , space_pred<char>() );

            std::string disciplineTitle;
            std::string disciplinePlace;
            split2pair(lectionsCommentStr, disciplineTitle, disciplinePlace, '-');
            trim( disciplineTitle , space_pred<char>() );
            trim( disciplinePlace , space_pred<char>() );

            auto dayInterval         = parseTimeInterval(lectionsTimeStr);
            auto totalMinutesInDay   = timeIntervalLen(dayInterval);
            acMinutesByDiscipline[disciplineTitle] += totalMinutesInDay;

            

            #ifdef DETAILED_OUT
                cout << "  Date     : " << dtStr << "\n";
                cout << "  Hours    : " << lectionsTimeStr << "\n";
                cout << "  Comment  : " << lectionsCommentStr << "\n";
                cout << "  Duration : " << formatMinutesToHours(totalMinutesInDay) << " (" << totalMinutesInDay << ")" << "\n";
            #endif

            /*
                Input: 17.05 10:00-15:00 к. 432 бух. учет Савенкова
                  Date     : 17.05
                  Hours    : 10:00-15:00
                  Comment  : к. 432 бух. учет Савенкова
                  Duration : 05:00 (300)
            
            */



            #ifdef DETAILED_OUT
                    cout << "\n";
            #endif

            auto lectionsTimeInterval = parseTimeInterval(lectionsTimeStr);

            std::vector< PairDetails > pairsSched;
            int dayAcMinutes = calcAcademicMinutesCount( lectionsTimeInterval
                                                       , bbp   
                                                       , bwp
                                                       , hrlen 
                                                       , pairsSched
                                                       );
            std::cout << dtStr << " " << lectionsTimeStr << " - ";
            std::cout << formatMinutesToHours(dayAcMinutes, 45);
            std::cout << " - ";
            printSched( pairsSched, ", ", false, false );
            std::cout << " - " << lectionsCommentStr;
            std::cout << "\n";

            totalAcMinutes += dayAcMinutes;
            weekAcMinutes  += dayAcMinutes;


            //trim( , space_pred<char>() );
            //trim( , space_pred<char>() );
       
        }
    }
    catch(const std::exception &e)
    {
        cerr << "Error: " << e.what() << "\n";
    }

    std::cout << "\n";
    //std::cout << "Total academic hours: " << formatMinutesToHours(totalAcMinutes, 45) << "\n";
    std::cout << "Academic hours by discipline:\n";
    std::map<std::string, int>::const_iterator dit = acMinutesByDiscipline.begin();
    for(; dit!=acMinutesByDiscipline.end(); ++dit)
    {
        std::cout << "  " << dit->first << ": " << formatMinutesToHours(dit->second, 45) << "\n";
    }
    
    //<< formatMinutesToHours(totalAcMinutes, 45) << "\n";

    


}









