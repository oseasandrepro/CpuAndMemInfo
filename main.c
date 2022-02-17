#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#define CONST_KBi 1048576.0

void GetCpuModel(char *str);
void GetTotalMemoryInGb(char *str);

int main(int argc, char* argv[])
{
	char cpuModel[100];
	char totalMemory[100];

	GtkBuilder	*builder;
	GtkWidget	*window;
	GtkWidget	*labelCpu;
	GtkWidget	*labelMemory;
 
	gtk_init(&argc , &argv);

	builder = gtk_builder_new_from_file("mainGui.glade");

	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	labelCpu = GTK_WIDGET(gtk_builder_get_object(builder, "labelCpu"));
	labelMemory = GTK_WIDGET(gtk_builder_get_object(builder, "labelMemory"));

	GetCpuModel(cpuModel);
	GetTotalMemoryInGb(totalMemory);

	gtk_label_set_text(GTK_LABEL(labelCpu), (const char*)cpuModel);
	gtk_label_set_text(GTK_LABEL(labelMemory), (const char*)totalMemory);

	gtk_widget_show(window);
	gtk_main();
	
	return 0;
}

void GetCpuModel(char *str)
{
	int i;
	FILE* arq = NULL;
	char aux[100];

	arq = fopen("/proc/cpuinfo", "r");

	if(arq == NULL)
		exit(1);

	for(i=0; i<5; i++)
		fgets(aux, 100, arq);
	fclose(arq);
	
	sscanf(aux, "%*s %*s : %[^\n]", str);
}

void GetTotalMemoryInGb(char *str)
{

	double memtotal = 0.0;
	FILE* arq = NULL;
	arq = fopen ("/proc/meminfo", "r");
	fscanf (arq,"%*[^:]: %lf", &memtotal);
	fclose(arq);

	memtotal /= CONST_KBi;

	sprintf(str, "%.3lf GB", memtotal);
}
