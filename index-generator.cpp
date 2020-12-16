#include "index-generator.h"
#include <QDebug>

using namespace std;

#define CONTENT "70比 69， 这是 男篮 亚锦赛 历史上 的 最小 分 差 比赛 ， 笑 到 最后 的是 东道主 中国队 。 可以说 ， 这是 一次 最 惊险 的 胜利 ； 也可 以 说 ， 这是 中国男篮 最 幸运 的 结局 。终 >  场 哨 响 ， 中国队 主教练 邓 华德 和 篮管中心 副主任 胡 加时 紧紧拥抱 在一 起 ， 两人 都 激动 得 热泪盈眶 —— 中国队 赢了 ， 赢得 很 庆幸 。"

#define TITLE "这 是 一条 新闻"

#define INDEX_PATH "./index_data"

#define F_DOCID 1

IndexGenerator::IndexGenerator(QObject *parent) : QObject(parent)
{
    try
        {
            //Text to be indexed
            string content(CONTENT);
            string title(TITLE);

            //Open an Database for write
            Xapian::WritableDatabase db(string(INDEX_PATH), Xapian::DB_CREATE_OR_OPEN);

            //Prepare TermGenerator, just split word by space, not chinese analysis
            Xapian::TermGenerator indexer;

            //Make Document
            Xapian::Document doc;
            doc.add_value(F_DOCID, string("1104"));
            doc.set_data(content);
            indexer.set_document(doc);
            indexer.index_text(title, 1, "T");
            indexer.index_text(content, 1, "C");

            //Add Document to db
            db.add_document(doc);

            //Flush to disk
            db.commit();
        }
        catch(const Xapian::Error &e)
        {
            qDebug()<<QString::fromStdString(e.get_description());
        }
        return;
}
