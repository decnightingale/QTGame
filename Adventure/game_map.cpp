#include "game_map.h"
#include "smallMap.h"
#include <QDebug>

game_map::game_map(QWidget* parent):QWidget(parent),light_value(100),life_value(10),money_value(20),collection_num(0),collection_list(0),located_point(0)
    ,collection_list_used(0),collection_num_used(0),paths(0)
{
    //设置随机数种子
    srand(time(0));

    smallMap* sm = new smallMap(this,QRect(0, 100, 100, 80));

    //状态栏声明
    m_board* status_icon = new m_board(this,false,":/image/status_board.png",300,100);
    status_icon->move(0,0);

    //生命值,灯火值声明
    QString life_string;
    life_string.setNum(life_value,10);
    QString light_string;
    light_string.setNum(light_value,10);
    QString money_string;
    money_string.setNum(money_value,10);
    QLabel* life_label = new QLabel(this);
    life_label->setText(life_string);
    life_label->move(70,40);
    QLabel* light_label = new QLabel(this);
    light_label->setText(light_string);
    light_label->move(170,40);
    QLabel* money_label = new QLabel(this);
    money_label->setText(money_string);
    money_label->move(240,60);

    //设置事件
    accident_point::actions.push_back(an_action(1, "直接走过尖刺。受到5点伤害","无视脚下的痛感，你以最快的速度通过了尖刺"
                                ,"尽管如此，还是有几根尖刺划伤了你的小腿。", "  ", 11, 2, -5));
    //"  。
    accident_point::actions.push_back(an_action(2, "尝试跳跃避开尖刺。有50%的概率不受伤害，否则受到10点伤害",
"你在布有尖刺的走廊中跳跃前行，试图避开地上的尖刺","突然，你背部着地地摔到了地上，后背被扎的鲜血淋漓",
"在几个高难度的跳跃后，你毫发无损地来到了走廊的另一端", 5, 2, -10));
    accident_point::actions.push_back(an_action(3, "取走一些药品，为目标回复15点生命","你取走了药品，用它处理了自己的伤口。"
,"你正想感谢老者的好意，却发现已经看不到他的身影。","", 11, 2, 15));
    accident_point::actions.push_back(an_action(4, "取走一盏提灯，增加10点灯火值","你取走了提灯，前路顿时光亮起来。"
,"你正想感谢老者的好意，却发现已经看不到他的身影。","", 10, 1, 10));
    accident_point::actions.push_back(an_action(5, "拼了命也要撬开！生命值降至1，获得一件特殊的藏品。","箱子里装着一顶王冠，它的诡异光泽让你头晕眼花，四肢无力，你赶快合上了它的盖子。"
,"你感到自己的状态很不对劲，但还是决定把这顶王冠带上。","", 10, 5, 0));
    accident_point::actions.push_back(an_action(6, "随手把箱子上的宝石拿走，获得20货币。"," 宝石受到了商人们的青睐，你获得了一大笔钱。"
,"但那个箱子里有什么呢，你心里仍存疑惑。","", 10, 3, 20));
    accident_point::actions.push_back(an_action(7, "生命值+6,灯火值-30,获得一件特殊的藏品。","行医向你讨要了一些灯油，用火焰和药膏开始治疗。"
,"虽然灯火变得昏暗了一些，但是你发现痛楚不再。","", 10, 4, 0));
    accident_point::actions.push_back(an_action(8, "获得2目标生命。"," 你谢绝了他的奇特偏方，表示用常规方法治疗便好。"
,"行医查看了你的病痛，给你了一些绷带和药水。","", 11, 2, 2));
    accident_point::actions.push_back(an_action(9, "接着下注。有10%的概率获得60货币","你把更多的注押在了那只甲壳虫上，焦急地等待结果。"
,"那只甲壳虫不负众望，获得了第一，你得到了应有的报酬。","那只甲壳虫不一会便泄了气，你原来赢的钱也输了回去", 1, 3, 60));
    accident_point::actions.push_back(an_action(10, "还是应该稳重一些。获得6货币。"," 你深知赌博的害处，选择明哲保身。"
,"你带着赢来的小钱离开了此地，耳后还回荡着叫喊声。","", 10, 3, 6));
    accident_point::incidents.push_back(an_incident("一条走廊出现在你的必经之路上。借着灯光，你发现在地面上有许多尖刺，直接走过去一定会受伤。", 0, 1));
    accident_point::incidents.push_back(an_incident("你和一位老者擦肩而过，你隐约听见随从低声唤他“圣徒”。老者叫住你，有些怀疑地盘问了一通，从何而来，所为何事。你从容且得体地回答了所有问题，他的语气缓和下来。良久，老者招呼随从取了一些补给，表示自己可以给予帮助。", 2, 3));
    accident_point::incidents.push_back(an_incident("你在荒地上找到了一个镶嵌珠宝的箱子，箱子的锁很结实，显示着内容物的重要性", 4, 5));
    accident_point::incidents.push_back(an_incident("你在旅途当中得了某种热病，正万分痛苦之时，你遇到了一位行医，他表示自己有治疗这方面疾病的独家偏方，但需要你手上提灯的一些灯油。", 6, 7));
    accident_point::incidents.push_back(an_incident("你误入了一间奇怪的赛马场，这里的“马”是在地上奔走的甲壳虫，你随便给一只虫下注，没想到居然赢了一点小钱。", 8, 9));
    //设置上下左右移动按钮
    m_Button* up_button = new m_Button(this,true,":/image/up_arrow.png");
    up_button->move(680,-40);

    m_Button* right_button = new m_Button(this,true,":/image/right_arrow.png");
    right_button->move(725,0);

    m_Button* left_button = new m_Button(this,true,":/image/left_arrow.png");
    left_button->move(640,0);

    m_Button* down_button = new m_Button(this,true,":/image/down_arrow.png");
    down_button->move(680,40);

    //设置左下角返回主菜单按钮
    //m_Button* return_button = new m_Button(this,false,":/image/game_map_return_button.png");
    //return_button->move(0,500);
    //connect(return_button,&m_Button::clicked,[=](){
    //    emit return_called();
    //});

    //设置帮助按钮//注：目前帮助仍然是主界面的帮助菜单，应该要加一个有关游戏地图的动态帮助窗口，类似于节点说明
    //m_Button* help_button = new m_Button(this,false,":/image/game_map_help_button.png");
    //help_button->move(130,500);
    //connect(help_button,&m_Button::clicked,[=](){
    //    emit help_called();
    //});

    //收藏品标识设置
    m_board* c_icon = new m_board(this,false,":/image/c_board.png",100,100);
    c_icon->move(0,490);
    collection_symbol* collection_symbol_1 = new collection_symbol(this);
    collection_symbol_1->move(0,500);
    connect(collection_symbol_1,&collection_symbol::clicked,[=](){
        collection_symbol_1->list = collection_list;
        collection_symbol_1->num = collection_num;
    });
    connect(collection_symbol_1,&collection_symbol::clicked,collection_symbol_1,&collection_symbol::clicked_action);

    //初始节点设置，按动会跳出节点说明动态窗口c
    start_point* start_point_ = new start_point(this);
    start_point_->move(333,91);
    connect(start_point_,&start_point::clicked,start_point_,&start_point::clicked_action);
    arrow_connect_tool(up_button,down_button,left_button,right_button,start_point_);
    start_point_->change_can_chosen();

    //宝藏节点设置
    int rank1=rand()%4+4;
    collection_num_used++;
    collection_list_used ^= (1<<rank1);
    treasure_point* treasure_point_1 = new treasure_point(this,rank1);
    treasure_point_1->move(367,754);
    connect(treasure_point_1,&treasure_point::clicked,treasure_point_1,&treasure_point::clicked_action);
    connect(treasure_point_1,&treasure_point::got_chosen,[=](){
        set_located_point(treasure_point_1);
        collection_num++;
        collection_list ^= (1<<rank1);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,treasure_point_1);

    branch_point* branch_point_1 = new branch_point(this);
    branch_point_1->move(490,1249);
    connect(branch_point_1,&branch_point::clicked,[=](){
        branch_point_1->money = money_value;
        branch_point_1->life_value = life_value;
        branch_point_1->light_value = light_value;
        branch_point_1->used_list = collection_list_used;
        branch_point_1->used_num = collection_num_used;
    });
    connect(branch_point_1,&branch_point::clicked,branch_point_1,&branch_point::clicked_action);
    connect(branch_point_1,&branch_point::got_chosen,[=](){
        set_located_point(branch_point_1);
    });
    connect(branch_point_1,&branch_point::buy_end,[=](){
        int s = branch_point_1->buy_sum;
        for (int var = 0; var < s; ++var) {
            collection_num++;
            collection_list ^= (1<<branch_point_1->buy_rank[var]);
            collection_num_used++;
            collection_list_used ^= (1<<branch_point_1->buy_rank[var]);
        }
        money_value = branch_point_1->money;
        money_label->setNum(money_value);
        life_value = branch_point_1->life_value;
        life_label->setNum(life_value);
        light_value = branch_point_1->light_value;
        light_label->setNum(light_value);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,branch_point_1);

    int rank2=rand()%4;
    collection_num_used++;
    collection_list_used ^= (1<<rank2);
    treasure_point* treasure_point_3 = new treasure_point(this,rank2);
    treasure_point_3->move(965,1100);
    connect(treasure_point_3,&treasure_point::clicked,treasure_point_3,&treasure_point::clicked_action);
    connect(treasure_point_3,&treasure_point::got_chosen,[=](){
        set_located_point(treasure_point_3);
        collection_num++;
        collection_list ^= (1<<rank2);
        if(treasure_point_3->rank==0)
        {
            light_value+=30;
            if(light_value>100)
                light_value=100;
            light_label->setNum(light_value);
        }
        if(treasure_point_3->rank==1)
        {
            life_value+=6;
            life_label->setNum(life_value);
        }
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,treasure_point_3);



    //战斗节点设置
    war_point* war_point_1 = new war_point(this);
    war_point_1->move(727,257);
    connect(war_point_1,&war_point::clicked,[=](){
        war_point_1->money = money_value;
        war_point_1->life_value = life_value;
        war_point_1->light_value = light_value;
        war_point_1->collection_list = collection_list;
    });
    connect(war_point_1,&war_point::clicked,war_point_1,&war_point::clicked_action);
    connect(war_point_1,&war_point::got_chosen,[=](){
        set_located_point(war_point_1);
    });
    connect(war_point_1,&war_point::battle_end,[=](){
        money_value = war_point_1->money;
        money_label->setNum(money_value);
        life_value = war_point_1->life_value;
        life_label->setNum(life_value);
        light_value = war_point_1->light_value;
        light_label->setNum(light_value);
        if(life_value==0)
            emit lose_sign();
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,war_point_1);

    war_point* war_point_2 = new war_point(this);
    war_point_2->move(560,988);
    connect(war_point_2,&war_point::clicked,[=](){
        war_point_2->money = money_value;
        war_point_2->life_value = life_value;
        war_point_2->light_value = light_value;
        war_point_2->collection_list = collection_list;
    });
    connect(war_point_2,&war_point::clicked,war_point_2,&war_point::clicked_action);
    connect(war_point_2,&war_point::got_chosen,[=](){
        set_located_point(war_point_2);
    });
    connect(war_point_2,&war_point::battle_end,[=](){
        money_value = war_point_2->money;
        money_label->setNum(money_value);
        life_value = war_point_2->life_value;
        life_label->setNum(life_value);
        light_value = war_point_2->light_value;
        light_label->setNum(light_value);
        if(life_value==0)
            emit lose_sign();
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,war_point_2);

    war_point* war_point_3 = new war_point(this);
    war_point_3->move(206,1234);
    connect(war_point_3,&war_point::clicked,[=](){
        war_point_3->money = money_value;
        war_point_3->life_value = life_value;
        war_point_3->light_value = light_value;
        war_point_3->collection_list = collection_list;
    });
    connect(war_point_3,&war_point::clicked,war_point_3,&war_point::clicked_action);
    connect(war_point_3,&war_point::got_chosen,[=](){
        set_located_point(war_point_3);
    });
    connect(war_point_3,&war_point::battle_end,[=](){
        money_value = war_point_3->money;
        money_label->setNum(money_value);
        life_value = war_point_3->life_value;
        life_label->setNum(life_value);
        light_value = war_point_3->light_value;
        light_label->setNum(light_value);
        if(life_value==0)
            emit lose_sign();
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,war_point_3);

    war_point* war_point_4 = new war_point(this);
    war_point_4->move(1242,863);
    connect(war_point_4,&war_point::clicked,[=](){
        war_point_4->money = money_value;
        war_point_4->life_value = life_value;
        war_point_4->light_value = light_value;
        war_point_4->collection_list = collection_list;
    });
    connect(war_point_4,&war_point::clicked,war_point_4,&war_point::clicked_action);
    connect(war_point_4,&war_point::got_chosen,[=](){
        set_located_point(war_point_4);
    });
    connect(war_point_4,&war_point::battle_end,[=](){
        money_value = war_point_4->money;
        money_label->setNum(money_value);
        life_value = war_point_4->life_value;
        life_label->setNum(life_value);
        light_value = war_point_4->light_value;
        light_label->setNum(light_value);
        if(life_value==0)
            emit lose_sign();
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,war_point_4);

    war_point* war_point_5 = new war_point(this);
    war_point_5->move(1213,396);
    connect(war_point_5,&war_point::clicked,[=](){
        war_point_5->money = money_value;
        war_point_5->life_value = life_value;
        war_point_5->light_value = light_value;
        war_point_5->collection_list = collection_list;
    });
    connect(war_point_5,&war_point::clicked,war_point_5,&war_point::clicked_action);
    connect(war_point_5,&war_point::got_chosen,[=](){
        set_located_point(war_point_5);
    });
    connect(war_point_5,&war_point::battle_end,[=](){
        money_value = war_point_5->money;
        money_label->setNum(money_value);
        life_value = war_point_5->life_value;
        life_label->setNum(life_value);
        light_value = war_point_5->light_value;
        light_label->setNum(light_value);
        if(life_value==0)
            emit lose_sign();
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,war_point_5);

    //剧情节点设置
    story_point* story_point_1 = new story_point(this);
    story_point_1->move(724,650);
    connect(story_point_1,&story_point::clicked,[=](){
        story_point_1->money = money_value;
        story_point_1->life_value = life_value;
        story_point_1->light_value = light_value;
        story_point_1->collection_list = collection_list;
    });
    connect(story_point_1,&story_point::clicked,story_point_1,&story_point::clicked_action);
    connect(story_point_1,&story_point::got_chosen,[=](){
        set_located_point(story_point_1);
    });
    connect(story_point_1,&story_point::battle_end,[=](){
        money_value = story_point_1->money;
        money_label->setNum(money_value);
        life_value = story_point_1->life_value;
        life_label->setNum(life_value);
        light_value = story_point_1->light_value;
        light_label->setNum(light_value);
        if(life_value==0)
            emit lose_sign();
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,story_point_1);

    story_point* story_point_2 = new story_point(this);
    story_point_2->move(225,982);
    connect(story_point_2,&story_point::clicked,[=](){
        story_point_2->money = money_value;
        story_point_2->life_value = life_value;
        story_point_2->light_value = light_value;
        story_point_2->collection_list = collection_list;
    });
    connect(story_point_2,&story_point::clicked,story_point_2,&story_point::clicked_action);
    connect(story_point_2,&story_point::got_chosen,[=](){
        set_located_point(story_point_2);
    });
    connect(story_point_2,&story_point::battle_end,[=](){
        money_value = story_point_2->money;
        money_label->setNum(money_value);
        life_value = story_point_2->life_value;
        life_label->setNum(life_value);
        light_value = story_point_2->light_value;
        light_label->setNum(light_value);
        if(life_value==0)
            emit lose_sign();
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,story_point_2);

    story_point* story_point_3 = new story_point(this);
    story_point_3->move(631,1736);
    connect(story_point_3,&story_point::clicked,[=](){
        story_point_3->money = money_value;
        story_point_3->life_value = life_value;
        story_point_3->light_value = light_value;
        story_point_3->collection_list = collection_list;
    });
    connect(story_point_3,&story_point::clicked,story_point_3,&story_point::clicked_action);
    connect(story_point_3,&story_point::got_chosen,[=](){
        set_located_point(story_point_3);
    });
    connect(story_point_3,&story_point::battle_end,[=](){
        money_value = story_point_3->money;
        money_label->setNum(money_value);
        life_value = story_point_3->life_value;
        life_label->setNum(life_value);
        light_value = story_point_3->light_value;
        light_label->setNum(light_value);
        if(life_value==0)
            emit lose_sign();
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,story_point_3);

    branch_point* branch_point_2 = new branch_point(this);
    branch_point_2->move(1540,1281);
    connect(branch_point_2,&branch_point::clicked,[=](){
        branch_point_2->money = money_value;
        branch_point_2->life_value = life_value;
        branch_point_2->light_value = light_value;
        branch_point_2->used_list = collection_list_used;
        branch_point_2->used_num = collection_num_used;
    });
    connect(branch_point_2,&branch_point::clicked,branch_point_2,&branch_point::clicked_action);
    connect(branch_point_2,&branch_point::got_chosen,[=](){
        set_located_point(branch_point_2);
    });
    connect(branch_point_2,&branch_point::buy_end,[=](){
        int s = branch_point_2->buy_sum;
        for (int var = 0; var < s; ++var) {
            collection_num_used++;
            collection_list_used ^= (1<<branch_point_2->buy_rank[var]);
            collection_num++;
            collection_list ^= (1<<branch_point_2->buy_rank[var]);
        }
        money_value = branch_point_2->money;
        money_label->setNum(money_value);
        life_value = branch_point_2->life_value;
        life_label->setNum(life_value);
        light_value = branch_point_2->light_value;
        light_label->setNum(light_value);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,branch_point_2);

    story_point* story_point_5 = new story_point(this);
    story_point_5->move(1474,427);
    connect(story_point_5,&story_point::clicked,[=](){
        story_point_5->money = money_value;
        story_point_5->life_value = life_value;
        story_point_5->light_value = light_value;
        story_point_5->collection_list = collection_list;
    });
    connect(story_point_5,&story_point::clicked,story_point_5,&story_point::clicked_action);
    connect(story_point_5,&story_point::got_chosen,[=](){
        set_located_point(story_point_5);
    });
    connect(story_point_5,&story_point::battle_end,[=](){
        money_value = story_point_5->money;
        money_label->setNum(money_value);
        life_value = story_point_5->life_value;
        life_label->setNum(life_value);
        light_value = story_point_5->light_value;
        light_label->setNum(light_value);
        if(life_value==0)
            emit lose_sign();
        else
            emit win_sign();
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,story_point_5);


    //事件节点设置
    accident_point* accident_point_1 = new accident_point(this);
    accident_point_1->move(240,496);
    connect(accident_point_1,&accident_point::clicked,[=](){
        copy_acc(accident_point_1);
    });
    connect(accident_point_1,&accident_point::clicked,accident_point_1,&accident_point::clicked_action);
    connect(accident_point_1,&accident_point::got_chosen,[=](){
        restore_acc(accident_point_1);
        life_label->setNum(life_value);
        light_label->setNum(light_value);
        money_label->setNum(money_value);
        set_located_point(accident_point_1);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,accident_point_1);

    accident_point* accident_point_2 = new accident_point(this);
    accident_point_2->move(575,442);
    connect(accident_point_2,&accident_point::clicked,[=](){
        copy_acc(accident_point_2);
    });
    connect(accident_point_2,&accident_point::clicked,accident_point_2,&accident_point::clicked_action);
    connect(accident_point_2,&accident_point::got_chosen,[=](){
        restore_acc(accident_point_2);
        life_label->setNum(life_value);
        light_label->setNum(light_value);
        money_label->setNum(money_value);
        set_located_point(accident_point_2);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,accident_point_2);

    accident_point* accident_point_3 = new accident_point(this);
    accident_point_3->move(-80,1426);
    accident_point_3->typ = 2;
    connect(accident_point_3,&accident_point::clicked,[=](){
        copy_acc(accident_point_3);
    });
    connect(accident_point_3,&accident_point::clicked,accident_point_3,&accident_point::clicked_action);
    connect(accident_point_3,&accident_point::got_chosen,[=](){
        restore_acc(accident_point_3);
        life_label->setNum(life_value);
        light_label->setNum(light_value);
        money_label->setNum(money_value);
        set_located_point(accident_point_3);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,accident_point_3);

    accident_point* accident_point_4 = new accident_point(this);
    accident_point_4->move(518,1501);
    connect(accident_point_4,&accident_point::clicked,[=](){
        copy_acc(accident_point_4);
    });
    connect(accident_point_4,&accident_point::clicked,accident_point_4,&accident_point::clicked_action);
    connect(accident_point_4,&accident_point::got_chosen,[=](){
        restore_acc(accident_point_4);
        life_label->setNum(life_value);
        light_label->setNum(light_value);
        money_label->setNum(money_value);
        set_located_point(accident_point_4);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,accident_point_4);

    accident_point* accident_point_5 = new accident_point(this);
    accident_point_5->move(1279,1257);
    accident_point_5->typ = 3;
    connect(accident_point_5,&accident_point::clicked,[=](){
        copy_acc(accident_point_5);
    });
    connect(accident_point_5,&accident_point::clicked,accident_point_5,&accident_point::clicked_action);
    connect(accident_point_5,&accident_point::got_chosen,[=](){
        restore_acc(accident_point_5);
        life_label->setNum(life_value);
        light_label->setNum(light_value);
        money_label->setNum(money_value);
        set_located_point(accident_point_5);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,accident_point_5);

    accident_point* accident_point_6 = new accident_point(this);
    accident_point_6->move(930,820);
    connect(accident_point_6,&accident_point::clicked,[=](){
        copy_acc(accident_point_6);
    });
    connect(accident_point_6,&accident_point::clicked,accident_point_6,&accident_point::clicked_action);
    connect(accident_point_6,&accident_point::got_chosen,[=](){
        restore_acc(accident_point_6);
        life_label->setNum(life_value);
        light_label->setNum(light_value);
        money_label->setNum(money_value);
        set_located_point(accident_point_6);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,accident_point_6);

    accident_point* accident_point_7 = new accident_point(this);
    accident_point_7->move(968,353);
    connect(accident_point_7,&accident_point::clicked,[=](){
        copy_acc(accident_point_7);
    });
    connect(accident_point_7,&accident_point::clicked,accident_point_7,&accident_point::clicked_action);
    connect(accident_point_7,&accident_point::got_chosen,[=](){
        restore_acc(accident_point_7);
        life_label->setNum(life_value);
        light_label->setNum(light_value);
        money_label->setNum(money_value);
        set_located_point(accident_point_7);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,accident_point_7);


    //连接各节点，制成地图
    start_point_->connect_to(accident_point_1);
    start_point_->connect_to(accident_point_2);
    start_point_->connect_to(war_point_1);
    story_point_1->connect_to(accident_point_2);
    story_point_1->connect_to(war_point_1);
    treasure_point_1->connect_to(accident_point_1);
    treasure_point_1->connect_to(story_point_1);
    treasure_point_1->connect_to(story_point_2);
    treasure_point_1->connect_to(war_point_2);
    story_point_2->connect_to(war_point_2);
    story_point_2->connect_to(branch_point_1);
    story_point_2->connect_to(war_point_3);
    war_point_3->connect_to(accident_point_3);
    war_point_3->connect_to(accident_point_4);
    accident_point_3->connect_to(story_point_3);
    accident_point_5->connect_to(treasure_point_3);
    accident_point_5->connect_to(accident_point_4);
    accident_point_5->connect_to(story_point_3);
    accident_point_5->connect_to(branch_point_2);
    treasure_point_3->connect_to(war_point_4);
    accident_point_6->connect_to(treasure_point_3);
    accident_point_6->connect_to(war_point_4);
    accident_point_6->connect_to(accident_point_7);
    accident_point_7->connect_to(war_point_5);
    war_point_5->connect_to(story_point_5);

    //设定每个节点的下个选项节点
    start_point_->add_forward_point(accident_point_1);
    start_point_->add_forward_point(accident_point_2);
    start_point_->add_forward_point(war_point_1);
    accident_point_1->add_forward_point(treasure_point_1);
    accident_point_2->add_forward_point(story_point_1);
    war_point_1->add_forward_point(story_point_1);
    story_point_1->add_forward_point(treasure_point_1);
    treasure_point_1->add_forward_point(story_point_2);
    treasure_point_1->add_forward_point(war_point_2);
    war_point_2->add_forward_point(story_point_2);
    story_point_2->add_forward_point(war_point_3);
    story_point_2->add_forward_point(branch_point_1);
    branch_point_1->add_forward_point(story_point_2);
    war_point_3->add_forward_point(accident_point_3);
    war_point_3->add_forward_point(accident_point_4);
    accident_point_3->add_forward_point(story_point_3);
    accident_point_4->add_forward_point(accident_point_5);
    story_point_3->add_forward_point(accident_point_5);
    accident_point_5->add_forward_point(branch_point_2);
    accident_point_5->add_forward_point(treasure_point_3);
    treasure_point_3->add_forward_point(accident_point_6);
    treasure_point_3->add_forward_point(war_point_4);
    war_point_4->add_forward_point(accident_point_6);
    accident_point_6->add_forward_point(accident_point_7);
    accident_point_7->add_forward_point(war_point_5);
    war_point_5->add_forward_point(story_point_5);

    //QGraphicsScene* path_scene = new QGraphicsScene(this);
    //QPen path_pen(Qt::blue, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    //path_scene->addLine(100,100,200,200,path_pen);
    //QGraphicsView* path_view = new QGraphicsView(path_scene,this);

    //设置初始节点为start_point;
    set_located_point(start_point_);

    //把视野控制按钮放到最顶层
    up_button->raise();
    down_button->raise();
    right_button->raise();
    left_button->raise();

    status_icon->raise();
    life_label->raise();
    light_label->raise();
    money_label->raise();

    c_icon->raise();
    collection_symbol_1->raise();
    sm->raise();


    //路径设置
    paths.push_back(QLine(start_point_->x()+25,start_point_->y()+25,accident_point_1->x()+25,accident_point_1->y()+25));
    paths.push_back(QLine(start_point_->x()+25,start_point_->y()+25,accident_point_2->x()+25,accident_point_2->y()+25));
    paths.push_back(QLine(start_point_->x()+25,start_point_->y()+25,war_point_1->x()+25,war_point_1->y()+25));
    paths.push_back(QLine(story_point_1->x()+25,story_point_1->y()+25,war_point_1->x()+25,war_point_1->y()+25));
    paths.push_back(QLine(story_point_1->x()+25,story_point_1->y()+25,accident_point_2->x()+25,accident_point_2->y()+25));
    paths.push_back(QLine(treasure_point_1->x()+25,treasure_point_1->y()+25,accident_point_1->x()+25,accident_point_1->y()+25));
    paths.push_back(QLine(treasure_point_1->x()+25,treasure_point_1->y()+25,story_point_1->x()+25,story_point_1->y()+25));
    paths.push_back(QLine(treasure_point_1->x()+25,treasure_point_1->y()+25,story_point_2->x()+25,story_point_2->y()+25));
    paths.push_back(QLine(treasure_point_1->x()+25,treasure_point_1->y()+25,war_point_2->x()+25,war_point_2->y()+25));
    paths.push_back(QLine(story_point_2->x()+25,story_point_2->y()+25,war_point_2->x()+25,war_point_2->y()+25));
    paths.push_back(QLine(story_point_2->x()+25,story_point_2->y()+25,branch_point_1->x()+25,branch_point_1->y()+25));
    paths.push_back(QLine(story_point_2->x()+25,story_point_2->y()+25,war_point_3->x()+25,war_point_3->y()+25));
    paths.push_back(QLine(war_point_3->x()+25,war_point_3->y()+25,accident_point_3->x()+25,accident_point_3->y()+25));
    paths.push_back(QLine(war_point_3->x()+25,war_point_3->y()+25,accident_point_4->x()+25,accident_point_4->y()+25));
    paths.push_back(QLine(accident_point_3->x()+25,accident_point_3->y()+25,story_point_3->x()+25,story_point_3->y()+25));
    paths.push_back(QLine(accident_point_5->x()+25,accident_point_5->y()+25,treasure_point_3->x()+25,treasure_point_3->y()+25));
    paths.push_back(QLine(accident_point_5->x()+25,accident_point_5->y()+25,accident_point_4->x()+25,accident_point_4->y()+25));
    paths.push_back(QLine(accident_point_5->x()+25,accident_point_5->y()+25,story_point_3->x()+25,story_point_3->y()+25));
    paths.push_back(QLine(accident_point_5->x()+25,accident_point_5->y()+25,branch_point_2->x()+25,branch_point_2->y()+25));
    paths.push_back(QLine(treasure_point_3->x()+25,treasure_point_3->y()+25,war_point_4->x()+25,war_point_4->y()+25));
    paths.push_back(QLine(accident_point_6->x()+25,accident_point_6->y()+25,treasure_point_3->x()+25,treasure_point_3->y()+25));
    paths.push_back(QLine(accident_point_6->x()+25,accident_point_6->y()+25,war_point_4->x()+25,war_point_4->y()+25));
    paths.push_back(QLine(accident_point_6->x()+25,accident_point_6->y()+25,accident_point_7->x()+25,accident_point_7->y()+25));
    paths.push_back(QLine(accident_point_7->x()+25,accident_point_7->y()+25,war_point_5->x()+25,war_point_5->y()+25));
    paths.push_back(QLine(war_point_5->x()+25,war_point_5->y()+25,story_point_5->x()+25,story_point_5->y()+25));


    //路径和视野按钮建立联系
    connect(down_button,&m_Button::clicked,[=](){
        typedef QList<QLine>::iterator IT;
        for(IT i = paths.begin();i!=paths.end();i++)
        {
            (*i).setLine((*i).x1(),(*i).y1()-50,(*i).x2(),(*i).y2()-50);
        }
        update();
    });
    connect(up_button,&m_Button::clicked,[=](){
        typedef QList<QLine>::iterator IT;
        for(IT i = paths.begin();i!=paths.end();i++)
        {
            (*i).setLine((*i).x1(),(*i).y1()+50,(*i).x2(),(*i).y2()+50);
        }
        update();
    });
    connect(left_button,&m_Button::clicked,[=](){
        typedef QList<QLine>::iterator IT;
        for(IT i = paths.begin();i!=paths.end();i++)
        {
            (*i).setLine((*i).x1()+50,(*i).y1(),(*i).x2()+50,(*i).y2());
        }
        update();
    });
    connect(right_button,&m_Button::clicked,[=](){
        typedef QList<QLine>::iterator IT;
        for(IT i = paths.begin();i!=paths.end();i++)
        {
            (*i).setLine((*i).x1()-50,(*i).y1(),(*i).x2()-50,(*i).y2());
        }
        update();
    });
}

void game_map::copy_acc(accident_point* aim)
{
    aim->collection_list = collection_list;
    aim->collection_list_used = collection_list_used;
    aim->collection_num = collection_num;
    aim->collection_num_used = collection_num_used;
    aim->life_value = life_value;
    aim->money_value = money_value;
    aim->light_value = light_value;
}

void game_map::restore_acc(accident_point* aim)
{
    collection_list = aim->collection_list;
    collection_list_used = aim->collection_list_used;
    collection_num = aim->collection_num;
    collection_num_used = aim->collection_num_used;
    life_value = aim->life_value;
    money_value = aim->money_value;
    light_value = aim->light_value;
}

//设置当前节点
void game_map::set_located_point(my_point* new_point)
{
    if(!new_point->can_be_chosen)
        return;
    if(located_point)
    {
        located_point->restore_located();
        int s =located_point->forward_num;
        for(int i=0;i<s;i++)
            located_point->forward_point[i]->close_can_chosen();
    }
    located_point = new_point;
    located_point->change_located();
    int sum = new_point->forward_num;
    for(int i=0;i<sum;i++)
        new_point->forward_point[i]->change_can_chosen();
}

//工具函数，建立各个节点和视野移动按钮之间的联系
void game_map::arrow_connect_tool(m_Button* up,m_Button* down,m_Button* left,m_Button* right,my_point* aim)
{
    connect(up,&m_Button::clicked,[=](){
        aim->move(aim->x(),aim->y()+50);
    });
    connect(down,&m_Button::clicked,[=](){
        aim->move(aim->x(),aim->y()-50);
    });
    connect(right,&m_Button::clicked,[=](){
        aim->move(aim->x()-50,aim->y());
    });
    connect(left,&m_Button::clicked,[=](){
        aim->move(aim->x()+50,aim->y());
    });
}

//绘制窗口背景
void game_map::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QImage img(":/image/game_map_bg.png");
    img=img.scaled(size(),Qt::KeepAspectRatioByExpanding);
    painter.drawImage(0,0,img);

    //关于小地图的尝试
    //QImage map(":/image/scaled_map.png");
    //map=map.scaled(200,160,Qt::KeepAspectRatioByExpanding);
    //painter.drawImage(0,30,map);

    QPixmap life_icon = QPixmap(":/image/life_icon.png").scaled(50,50);
    QPixmap light_icon = QPixmap(":/image/light_icon.png").scaled(50,50);
    QPixmap money_icon = QPixmap(":/image/money_icon.png").scaled(50,50);
    QPixmap status_icon = QPixmap(":/image/status_board.png").scaled(300,75);
    painter.drawPixmap(0,0,status_icon);
    painter.drawPixmap(0,0,life_icon);
    painter.drawPixmap(100,0,light_icon);
    painter.drawPixmap(200,0,money_icon);

    //绘制路径
    QPen path_pen;
    path_pen.setStyle(Qt::DashDotDotLine);
    path_pen.setWidth(5);
    path_pen.setBrush(Qt::white);
    path_pen.setCapStyle(Qt::RoundCap);
    painter.setPen(path_pen);
    painter.drawLines(paths);

}
