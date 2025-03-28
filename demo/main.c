/* NAppGUI Hello World */

#include <nappgui.h>

typedef struct _app_t App;

struct _app_t
{
    Window *window;
    Edit *edit;
};

/*---------------------------------------------------------------------------*/

static Panel *i_panel(App *app)
{
    Panel *panel = panel_create();
    Layout *layout = layout_create(1, 1);
    layout_margin(layout, 25);
    {
        Edit *edit = edit_create();
        edit_editable(edit, FALSE);
        edit_text(edit, "...");
        app->edit = edit;
        layout_edit(layout, edit, 0, 0);
    }
    panel_layout(panel, layout);
    return panel;
}

/*---------------------------------------------------------------------------*/

static void i_OnClose(App *app, Event *e)
{
    osapp_finish();
    unref(app);
    unref(e);
}

/*---------------------------------------------------------------------------*/

typedef byte_t* pbytet;
DeclSt(pbytet);

static App *i_create(void)
{
    App *app = heap_new0(App);
    Panel *panel = i_panel(app);
    app->window = window_create(ekWINDOW_STD);
    window_panel(app->window, panel);
    window_title(app->window, "Hello, World!");
    window_origin(app->window, v2df(500, 200));
    window_OnClose(app->window, listener(app, i_OnClose, App));
    window_show(app->window);

    Clock *clock = clock_create(.1);
    ArrSt(pbytet)* ptrs = arrst_create(pbytet);
    for(int i = 0; i < 10000000; i++) {
        pbytet* ptr = arrst_new(ptrs, pbytet);
        *ptr = heap_malloc(64, "test");
    }
    arrst_foreach(ptr, ptrs, pbytet)
        *ptr = heap_realloc(*ptr, 64, 128, "test");
    arrst_end()
    arrst_foreach(ptr, ptrs, pbytet)
        heap_free(ptr, 128, "test");
    arrst_end()
    arrst_destroy(&ptrs, NULL, pbytet);
    String* edit_str = str_printf("%f", clock_elapsed(clock));
    edit_text(app->edit, tc(edit_str));
    str_destroy(&edit_str);
    clock_destroy(&clock);

    return app;
}

/*---------------------------------------------------------------------------*/

static void i_destroy(App **app)
{
    window_destroy(&(*app)->window);
    heap_delete(app, App);
}

/*---------------------------------------------------------------------------*/

#include <osapp/osmain.h>
osmain(i_create, i_destroy, "", App)
