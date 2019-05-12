BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "TaskActivity" (
    "ID" INTEGER PRIMARY KEY NOT NULL,
	"Title"	    TEXT,
  	"Content"   TEXT,
	"Place"	    TEXT,
	"Account"	TEXT,               -- 账户

    "DateStart"	TEXT,               -- 格式为 "YYYY-MM-DD" 的日期
	"DateEnd"	TEXT,               -- 格式为 "YYYY-MM-DD" 的日期
    "DateType"  INTEGER DEFAULT 0,  -- 0: 阳历； 1: 农历
    "TimeStart" TEXT,               -- 格式为 "HH:MM:SS" 的时间
    "TimeEnd"   TEXT,               -- 格式为 "HH:MM:SS" 的时间

    /*
    0，一次性
    1，每天
    2，每周
    3，每月
    4，每年
    100，自定义
    */
	"Repeat"	INTEGER DEFAULT 0,
    
    /*
     以 , 分隔的时间，单位为分钟，
     正数表示在StartTime后，负数表示在StartTime前
     默认为-5分钟
    */
    "Prompt"    TEXT DEFAULT -5
);
COMMIT;
