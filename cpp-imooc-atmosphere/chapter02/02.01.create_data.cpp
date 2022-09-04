//==================================================================
// @author: 本程序用于生成全国气象站点观测的分钟数据。
// @description: 本程序用于生成全国气象站点观测的分钟数据。
//==================================================================

#include <lib/_public.h>
#include <lib/path.h>

#define TIME_FORMAT "yyyymmddhh24miss"

using namespace std;

// 全国气象站点参数结构体。
struct st_stcode {
    char prov_name[31]; // 省
    char obt_id[11];    // 站号
    char obt_name[31];  // 站名
    double lat;        // 纬度
    double lon;        // 经度
    double height;     // 海拔高度
};

// 全国气象站点分钟观测数据结构
struct st_surf_data {
    char obt_id[11];      // 站点代码。
    char date_time[21];  // 数据时间：格式由 TIME_FORMAT 定义
    int t;              // 气温：单位，0.1摄氏度。
    int p;              // 气压：0.1百帕。
    int u;              // 相对湿度，0-100之间的值。
    int wd;             // 风向，0-360之间的值。
    int wf;             // 风速：单位0.1m/s
    int r;              // 降雨量：0.1mm。
    int vis;            // 能见度：0.1米。
};

// 日志文件
CLogFile logfile;

// 观测数据的时间。
char dateTime[21];

void crtSurfData(vector<struct st_stcode> &codeList, vector<struct st_surf_data> &surfList);

bool loadStCode(const char *initFile, vector<struct st_stcode> &list);

bool crtSurfFile(vector<struct st_surf_data> &list, const char *outPath, const char *dataFormat);

int main(int argc, char *argv[]) {

    if (argc != 5) {
        printf("Using: ./02.01.create_data ini_file out_path log_file dataFormat\n");
        printf("Example: ./02.01.create_data ../../data/stcode.ini ../out/idc/surf_data ../log/idc/02.01.sample.log xml,json,csv\n\n");
        printf("ini_file 全国气象站点参数文件名。\n");
        printf("out_path 全国气象站点数据文件存放的目录。\n");
        printf("log_file 本程序运行的日志文件名。\n\n");
        printf("dataFormat 生成数据文件的格式，支持 xml、json 和 csv 三种格式，中间用逗号分隔。\n\n");
        return EXIT_FAILURE;
    }

    // 打开程序的日志文件。
    if (!logfile.Open(argv[3], "a+", false)) {
        printf("logfile.Open(%s) failed.\n", argv[3]);
        return -1;
    }

    logfile.Write("开始运行。\n");

    // 存放全国气象站点参数的容器。
    vector<struct st_stcode> stCodeList;
    // 把站点参数文件中加载到 stCodeList 容器中。
    if (!loadStCode(argv[1], stCodeList)) {
        printf("loadStCode(%s) failed. \n", argv[1]);
        return EXIT_FAILURE;
    }

    // 存放全国气象站点分钟观测数据的容器
    vector<struct st_surf_data> surfDataList;
    // 模拟生成全国气象站点分钟观测数据，存放在 surfDataList 容器中。
    crtSurfData(stCodeList, surfDataList);

    // 把容器 surfDataList 中的全国气象站点分钟观测数据写入文件。
    if (strstr(argv[4], "xml") != nullptr) {
        crtSurfFile(surfDataList, argv[2], "xml");
    }
    if (strstr(argv[4], "json") != nullptr) {
        crtSurfFile(surfDataList, argv[2], "json");
    }
    if (strstr(argv[4], "csv") != nullptr) {
        crtSurfFile(surfDataList, argv[2], "csv");
    }

    logfile.Write("运行结束。\n");

    return 0;
}

bool loadStCode(const char *initFile, vector<struct st_stcode> &list) {
    CFile file;

    //打开文件
    if (!file.Open(initFile, "r")) {
        logfile.Write("File.Open(%s) failed.\n", initFile);
        return false;
    }

    //字符串工具类
    CCmdStr CmdStr;
    char strBuffer[301];
    struct st_stcode stcode{};

    while (true) {
        // 从站点参数文件中读取一行，如果已读取完，跳出循环。
        if (!file.Fgets(strBuffer, 300, true)) {
            break;
        }

        // 把读取到的一行拆分。
        CmdStr.SplitToCmd(strBuffer, ",", true);

        // 扔掉无效的行。
        if (CmdStr.CmdCount() != 6) {
            continue;
        }

        // 把站点参数的每个数据项保存到站点参数结构体中。
        memset(&stcode, 0, sizeof(struct st_stcode));
        CmdStr.GetValue(0, stcode.prov_name, 30); // 省
        CmdStr.GetValue(1, stcode.obt_id, 10);    // 站号
        CmdStr.GetValue(2, stcode.obt_name, 30);  // 站名
        CmdStr.GetValue(3, &stcode.lat);         // 纬度
        CmdStr.GetValue(4, &stcode.lon);         // 经度
        CmdStr.GetValue(5, &stcode.height);      // 海拔高度

        // 把站点参数结构体放入站点参数容器。
        list.push_back(stcode);
    }

    printf("read count: %zu\n", list.size());
    return true;
}

void crtSurfData(vector<struct st_stcode> &codeList, vector<struct st_surf_data> &surfList) {
    // 播随机数种子。
    srand(time(nullptr)/*用当前时间做种子*/);

    // 获取当前时间，当作观测时间。
    memset(dateTime, 0, sizeof(dateTime));
    LocalTime(dateTime, TIME_FORMAT);

    struct st_surf_data surf_data{};

    // 遍历气象站点参数的 codeList 容器。
    for (auto &ii: codeList) {
        memset(&surf_data, 0, sizeof(struct st_surf_data));

        // 用随机数填充分钟观测数据的结构体。
        strncpy(surf_data.obt_id, ii.obt_id, 10);
        strncpy(surf_data.date_time, dateTime, 14);
        // 下面算法是模拟真实世界的数据，不用在意具体的为什么这么算。
        surf_data.t = rand() % 351;
        surf_data.p = rand() % 265 + 10000;
        surf_data.u = rand() % 100 + 1;
        surf_data.wd = rand() % 360;
        surf_data.wf = rand() % 150;
        surf_data.r = rand() % 16;
        surf_data.vis = rand() % 5001 + 100000;

        // 把观测数据的结构体放入 surfList 容器。
        surfList.push_back(surf_data);
    }

    printf("create count: %zu\n", surfList.size());
}

bool crtSurfFile(vector<struct st_surf_data> &list, const char *outPath, const char *dataFormat) {

    CFile file;

    // 拼接生成数据的文件名，例如：../out/idc/surf_data/SURF_ZH_20210629092200_2254.csv
    char strFileName[301];
    sprintf(strFileName, "%s/SURF_ZH_%s_%d.%s", outPath, dateTime, getpid(), dataFormat);

    // 打开文件。
    if (!file.OpenForRename(strFileName, "w")) {
        logfile.Write("File.OpenForRename(%s) failed.\n", strFileName);
        return false;
    }


    if (strcmp(dataFormat, "csv") == 0) {
        file.Fprintf("站点代码,数据时间,气温,气压,相对湿度,风向,风速,降雨量,能见度\n");
    }
    if (strcmp(dataFormat, "xml") == 0) {
        file.Fprintf("<data>\n");
    }
    if (strcmp(dataFormat, "json") == 0) {
        file.Fprintf("{\"data\":[\n");
    }

    // 遍历存放观测数据的 list 容器。
    for (int ii = 0; ii < list.size(); ii++) {

        // 写入一条记录。
        if (strcmp(dataFormat, "csv") == 0) {
            file.Fprintf("%s,%s,%.1f,%.1f,%d,%d,%.1f,%.1f,%.1f\n",
                         list[ii].obt_id, list[ii].date_time, list[ii].t / 10.0, list[ii].p / 10.0,
                         list[ii].u, list[ii].wd, list[ii].wf / 10.0, list[ii].r / 10.0, list[ii].vis / 10.0);
        }

        if (strcmp(dataFormat, "xml") == 0) {
            file.Fprintf(
                    "<obtid>%s</obtid><ddatetime>%s</ddatetime><t>%.1f</t><p>%.1f</p><u>%d</u><wd>%d</wd><wf>%.1f</wf><r>%.1f</r><vis>%.1f</vis><endl/>\n",
                    list[ii].obt_id, list[ii].date_time, list[ii].t / 10.0, list[ii].p / 10.0, list[ii].u, list[ii].wd,
                    list[ii].wf / 10.0, list[ii].r / 10.0, list[ii].vis / 10.0);
        }

        if (strcmp(dataFormat, "json") == 0) {
            file.Fprintf(
                    R"({"obtid":"%s","ddatetime":"%s","t":"%.1f","p":"%.1f","u":"%d","wd":"%d","wf":"%.1f","r":"%.1f","vis":"%.1f"})",
                    list[ii].obt_id, list[ii].date_time, list[ii].t / 10.0, list[ii].p / 10.0, list[ii].u, list[ii].wd,
                    list[ii].wf / 10.0, list[ii].r / 10.0, list[ii].vis / 10.0);

            if (ii < list.size() - 1) {
                file.Fprintf(",\n");
            } else {
                file.Fprintf("\n");
            }
        }

    }

    if (strcmp(dataFormat, "xml") == 0) {
        file.Fprintf("</data>\n");
    }
    if (strcmp(dataFormat, "json") == 0) {
        file.Fprintf("]}\n");
    }

    // 关闭文件。
    file.CloseAndRename();

    printf("生成数据文件 %s 成功，数据时间 %s，记录数 %zu。\n", strFileName, dataFormat, list.size());
    logfile.Write("生成数据文件 %s 成功，数据时间 %s，记录数 %d。\n", strFileName, dataFormat, list.size());

    return true;
}