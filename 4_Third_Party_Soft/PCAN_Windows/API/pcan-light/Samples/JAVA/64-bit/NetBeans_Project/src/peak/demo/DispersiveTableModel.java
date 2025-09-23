package peak.demo;

import java.util.Hashtable;

import javax.swing.table.AbstractTableModel;

/*
 * Created on 20.05.2004
 *
 */

public class DispersiveTableModel extends AbstractTableModel {

	private int rows;
	private int columns;
	private Hashtable data;

	public DispersiveTableModel(int rows, int columns){
		this.rows=rows;
		this.columns=columns;
		this.data=new Hashtable();
	}

	/* (non-Javadoc)
	 * @see javax.swing.table.TableModel#getRowCount()
	 */
	public int getRowCount() {
		return rows;
	}

	/* (non-Javadoc)
	 * @see javax.swing.table.TableModel#getColumnCount()
	 */
	public int getColumnCount() {
		return columns;
	}

	public String getColumnName(int columnIndex){
		return "C"+columnIndex;
	}

	public Class getColumnClass(int columnIndex){
		return String.class;
	}

	public boolean isCellEditable(int rowIndex, int columnIndex){
		return rowIndex<rows && columnIndex<columns;
	}

	/* (non-Javadoc)
	 * @see javax.swing.table.TableModel#getValueAt(int, int)
	 */
	public Object getValueAt(int rowIndex, int columnIndex) {
		String key="["+rowIndex+","+columnIndex+"]";
		String value = (String)data.get(key);
		return value==null?"":value;
	}

	public void setValueAt(Object aValue, int rowIndex, int columnIndex){
		String key="["+rowIndex+","+columnIndex+"]";
		String value = (String)aValue;
		if(value.length()<=0){
			data.remove(key);
		}else{
			data.put(key,value);
		}
	}
}
