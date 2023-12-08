#include "../src/unit_of_work.h"
#include "../src/drawing_mapper.h"
#include "../src/painter_mapper.h"
#include "../src/drawing.h"
#include "../src/triangle.h"

#include <sqlite3.h>
#include <string>
#include <iostream>
#include <list>
#include <memory>

using std::string;
using std::list;

class DBSuite : public ::testing::Test
{
protected:
    void SetUp() override {
        create_drawing_table();
        create_painter_table();
        populate_drawings();
        populate_painters();
        dm = DrawingMapper::instance();
        dm->setDB("resource/drawing.db");
        pm = PainterMapper::instance();
        pm->setDB("resource/painter.db");
    }

    void TearDown() override {
        drop_drawing_table();
        drop_painter_table();
        sqlite3_close(db);
        sqlite3_close(db_p);
    }

    void create_drawing_table() {
        ASSERT_EQ(0, sqlite3_open("resource/drawing.db", &db));
        const char *stmt = "CREATE TABLE drawing ("
                           "ID         char(6) PRIMARY KEY     not null,"
                           "painter    varchar(50)             not null,"
                           "shapes varchar(1028),"
                           "FOREIGN KEY(painter) REFERENCES painter(ID))";
        int rc = sqlite3_exec(db, stmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void drop_drawing_table() {
        const char *dropStmt = "DROP TABLE drawing";
        int rc = sqlite3_exec(db, dropStmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void create_painter_table() {
        ASSERT_EQ(0, sqlite3_open("resource/painter.db", &db_p));
        const char *stmt = "CREATE TABLE painter ("
                           "ID         char(6) PRIMARY KEY     not null,"
                           "name    varchar(50)             not null)";
        int rc = sqlite3_exec(db_p, stmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void drop_painter_table() {
        const char *dropStmt = "DROP TABLE painter";
        int rc = sqlite3_exec(db_p, dropStmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void populate_drawings() {
        const char *s1 = "INSERT INTO drawing"
                         "(ID, painter, shapes)"
                         "values"
                         "('d_0001', 'p_0001', 'triangle 1 1 1')";
        int rc = sqlite3_exec(db, s1, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);

        const char *s2 = "INSERT INTO drawing"
                         "(ID,  painter,   shapes)"
                         "values"
                         "('d_0002', 'p_0001', 'triangle 2 2 2')";
        rc = sqlite3_exec(db, s2, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);

        const char *s3 = "INSERT INTO drawing"
                         "(ID,  painter,   shapes)"
                         "values"
                         "('d_0003', 'p_0002', 'compound { triangle 1 1 1 triangle 2 2 2 } triangle 3 3 3')";
        rc = sqlite3_exec(db, s3, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);
    }

    void populate_painters() {
        const char *s1 = "INSERT INTO painter"
                         "(ID, name)"
                         "values"
                         "('p_0001', 'Patrick')";
        int rc = sqlite3_exec(db_p, s1, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);

        const char *s2 = "INSERT INTO painter"
                         "(ID, name)"
                         "values"
                         "('p_0002', 'Mary')";
        rc = sqlite3_exec(db_p, s2, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);
    }

    void display_err_msg_and_fail_if_any(int rc) {
        if (rc) {
            std::cout << "db error: " << err_msg << std::endl;
            sqlite3_free(err_msg);
        }
        ASSERT_EQ(SQLITE_OK, rc);
    }

    sqlite3 *db;
    sqlite3 *db_p;
    char *err_msg = nullptr;
    DrawingMapper *dm;
    PainterMapper *pm;
};

TEST_F(DBSuite, Sanity) {}

TEST_F(DBSuite, findDrawing) {
    Drawing * drawing = dm->find("d_0001");

    EXPECT_TRUE(UnitOfWork::instance()->inClean("d_0001"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("d_0001"));
    ASSERT_EQ(drawing->id(), "d_0001");
    ASSERT_EQ(drawing->getShape(0)->perimeter(), 3);

    EXPECT_TRUE(UnitOfWork::instance()->inClean("p_0001"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("p_0001"));
    ASSERT_EQ(drawing->painter()->id(), "p_0001");
    ASSERT_EQ(drawing->painter()->name(), "Patrick");
}

TEST_F(DBSuite, newPainter) {
    UnitOfWork * uow = UnitOfWork::instance();
    string id = "p_5566";
    string name = "David";

    Painter * painter = new Painter(id, name);
    uow->registerNew(painter);
    EXPECT_TRUE(uow->inNew(id));

    uow->commit();
    EXPECT_FALSE(uow->inNew(id));
    EXPECT_TRUE(uow->inClean(id));

    Painter * target = pm->find("p_5566");
    EXPECT_TRUE(uow->inClean("p_5566"));
    EXPECT_FALSE(uow->inDirty("p_5566"));

    EXPECT_EQ("p_5566", target->id());
    EXPECT_EQ(painter->name(), target->name());
}

TEST_F(DBSuite, newDrawingWithPainter) {
    UnitOfWork * uow = UnitOfWork::instance();

    Painter * painter = new Painter("p_9527", "Willy");
    uow->registerNew(painter);
    EXPECT_TRUE(uow->inNew(painter->id()));


    Drawing * drawing = new Drawing("d_9527", painter, {new Triangle(3, 3, 3)});
    uow->registerNew(drawing);
    EXPECT_TRUE(uow->inNew(drawing->id()));

    uow->commit();
    EXPECT_FALSE(uow->inNew(drawing->id()));
    EXPECT_TRUE(uow->inClean(drawing->id()));
    EXPECT_FALSE(uow->inNew(painter->id()));
    EXPECT_TRUE(uow->inClean(painter->id()));

    Drawing * target = dm->find("d_9527");
    EXPECT_TRUE(uow->inClean("d_9527"));
    EXPECT_FALSE(uow->inDirty("d_9527"));

    EXPECT_EQ(drawing->id(), target->id());
    EXPECT_EQ(drawing->getShape(0)->perimeter(), 9);

    EXPECT_EQ(painter->id(), target->painter()->id());
    EXPECT_EQ(painter->name(), target->painter()->name());
}

TEST_F(DBSuite, updatePainter) {
    UnitOfWork * uow = UnitOfWork::instance();

    Painter * painter = pm->find("p_0001");
    EXPECT_TRUE(uow->inClean("p_0001"));
    EXPECT_FALSE(uow->inDirty("p_0001"));
    EXPECT_EQ(painter->id(), "p_0001");
    EXPECT_EQ(painter->name(), "Patrick");

    painter->setName("Mary");
    EXPECT_FALSE(uow->inClean(painter->id()));
    EXPECT_TRUE(uow->inDirty(painter->id()));
    EXPECT_EQ(painter->name(), "Mary");

    uow->commit();
    EXPECT_FALSE(uow->inDirty(painter->id()));
    EXPECT_TRUE(uow->inClean(painter->id()));

    Painter * target = pm->find("p_0001");
    EXPECT_TRUE(uow->inClean("p_0001"));
    EXPECT_FALSE(uow->inDirty("p_0001"));
    EXPECT_EQ(target->name(), "Mary");
}

TEST_F(DBSuite, updateDrawingWithPainter) {
    UnitOfWork * uow = UnitOfWork::instance();

    Painter * painter = new Painter("p_3333", "Verstappen");
    uow->registerNew(painter);
    EXPECT_TRUE(uow->inNew(painter->id()));

    Drawing * drawing = dm->find("d_0002");
    EXPECT_TRUE(uow->inClean("d_0002"));
    EXPECT_FALSE(uow->inDirty("d_0002"));
    EXPECT_EQ("d_0002", drawing->id());
    
    drawing->setPainter(painter);
    EXPECT_TRUE(uow->inDirty(drawing->id()));
    EXPECT_FALSE(uow->inClean(drawing->id()));
    EXPECT_EQ("p_3333", drawing->painter()->id());
    EXPECT_EQ("Verstappen", drawing->painter()->name());

    uow->commit();
    EXPECT_TRUE(uow->inClean(drawing->id()));
    EXPECT_FALSE(uow->inDirty(drawing->id()));
    EXPECT_TRUE(uow->inClean(painter->id()));
    EXPECT_FALSE(uow->inNew(painter->id()));

    Drawing * target = dm->find("d_0002");
    EXPECT_EQ("d_0002", target->id());
    EXPECT_EQ("p_3333", target->painter()->id());
    EXPECT_EQ("Verstappen", target->painter()->name());
}

TEST_F(DBSuite, deletePainter) {
    UnitOfWork * uow = UnitOfWork::instance();

    Painter * painter = pm->find("p_0002");
    uow->registerDeleted(painter);
    EXPECT_TRUE(uow->inDeleted(painter->id()));
    EXPECT_FALSE(uow->inClean(painter->id()));

    uow->commit();
    EXPECT_FALSE(uow->inDeleted("p_0002"));

    Painter * target = pm->find("p_0002");
    EXPECT_EQ(target, nullptr);
}

TEST_F(DBSuite, deletePainterWithoutCommit) {
    UnitOfWork * uow = UnitOfWork::instance();

    Painter * painter = new Painter("p_4444", "Lewis");
    uow->registerNew(painter);
    EXPECT_TRUE(uow->inNew(painter->id()));
    EXPECT_FALSE(uow->inClean(painter->id()));

    uow->registerDeleted(painter);
    EXPECT_FALSE(uow->inDeleted(painter->id()));
    EXPECT_FALSE(uow->inNew(painter->id()));
}

TEST_F(DBSuite, deleteDrawing) {
    UnitOfWork * uow = UnitOfWork::instance();

    Drawing * drawing = dm->find("d_0003");
    uow->registerDeleted(drawing);
    EXPECT_TRUE(uow->inDeleted(drawing->id()));
    EXPECT_FALSE(uow->inClean(drawing->id()));

    uow->commit();
    EXPECT_FALSE(uow->inDeleted("d_0003"));

    Drawing * target = dm->find("d_0003");
    EXPECT_EQ(target, nullptr);
}