#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <gtkmm.h>

enum {
	CT_FILE,
	CT_DIR_UNLOADED,
	CT_DIR_LOADED,
	CT_ADDER
};

class CNavigationView {
public:
	class Columns : public Gtk::TreeModel::ColumnRecord {
	public:
		Columns();
		
		Gtk::TreeModelColumn<Glib::ustring> name;
		Gtk::TreeModelColumn<Glib::ustring> full_path;
		Gtk::TreeModelColumn<Glib::ustring> ext;
		Gtk::TreeModelColumn<Glib::ustring> ord;
		Gtk::TreeModelColumn<int> type;
	};
	
	Columns cols;

	CNavigationView(std::string base_path);

	std::string base;
	
	Gtk::TreeView *v;
	/*Gtk::CellRendererText name_renderer;
	Gtk::CellRendererPixbuf icon_renderer;
	Gtk::TreeViewColumn name_col;*/
	
	Glib::RefPtr<Gtk::TreeStore> store;
	
	std::string Row2Path(Gtk::TreeModel::iterator row);

	void AttachView(Gtk::TreeView *v);
	void ExpandDirectory(std::string path, const Gtk::TreeNodeChildren *node);
	
	void HandleRename(std::string oldname, std::string newname);
	void FixPaths(std::string path, const Gtk::TreeNodeChildren *node);
	
	void CreateAdder(Gtk::TreeModel::iterator row);
	
	void on_row_edit_start(Gtk::CellEditable* cell_editable, const Glib::ustring& path);
	void on_row_edit_commit(const Glib::ustring& path_string, const Glib::ustring& new_text);
	void on_row_activated(const Gtk::TreeModel::Path &path, const Gtk::TreeViewColumn *col);
	bool on_expand_row(const Gtk::TreeModel::iterator& iter, const Gtk::TreeModel::Path& path);
	
	sigc::connection conns[4];
};

#endif