import numpy as np
import pandas as pd
import plotly.plotly as py
import plotly.graph_objs as go
import os

def line_chart(dataframe, title, ax_name, ay_name, traces, path):
    
    trace0 = go.Scatter(
        x = dataframe.columns,
        y = dataframe.loc[traces[0]],
        mode = 'lines+markers',
        name = str(traces[0])+' x '+str(traces[0])
    )
    trace1 = go.Scatter(
        x = dataframe.columns,
        y = dataframe.loc[traces[1]],
        mode = 'lines+markers',
        name = str(traces[1])+' x '+str(traces[1])
    )
    trace2 = go.Scatter(
        x = dataframe.columns,
        y = dataframe.loc[traces[2]],
        mode = 'lines+markers',
        name = str(traces[2])+' x '+str(traces[2])
    )

    data = [trace0, trace1, trace2]

    layout = go.Layout(
        title=title,
        xaxis={'title': ax_name, 'type':'category'},
        yaxis={'title': ay_name}        
    )

    fig = go.Figure(data=data, layout=layout)
    py.image.save_as(fig, filename=path)
    py.iplot(fig, filename='error-bar-bar')



# gerando dataframes a partir dos arquivos

list_n = [1000, 5000, 10000]
list_p = [2, 4, 8]
list_t = [4, 8]

data_set      = dict([(n, []) for n in list_n])
error_set     = dict([(n, []) for n in list_n])
data_set_seq  = dict([(n, []) for n in list_n])

with open('../logs/tempos.txt', 'r') as f, open('../logs/tempos_seq.txt', 'r') as f_seq:
    for n in list_n:
        values_seq = [float(f_seq.readline()) for i in range(5)]
        
        data_set_seq[n].append(np.mean(values_seq))
        data_set_seq[n].append(np.std(values_seq))
        
        for p in list_p:
            for t in list_t:
                values = [float(f.readline()) for i in range(5)]
                
                data_set[n].append(np.mean(values))
                error_set[n].append(np.std(values))


data_labels = [str(p)+', '+str(t) for p in list_p for t in list_t ]

df_data = pd.DataFrame.from_dict(data_set, orient='index')/60
df_error = pd.DataFrame.from_dict(error_set, orient='index')/60
df_data_seq = pd.DataFrame.from_dict(data_set_seq, orient='index')/60

df_data.columns = data_labels
df_error.columns = data_labels
df_data_seq.columns = ["tempo", "erro"]

df_media_parallel = pd.DataFrame()
df_media_parallel['tempo'] = df_data.mean(axis=1);
df_media_parallel['erro'] =  df_error.mean(axis=1);

# SPEEDUP
df_speedup = df_data.divide(df_data_seq['tempo'], axis=0)

# EFICIENCIA
pt = [p*t for p in list_p for t in list_t]
df_eficiencia = df_speedup.divide(pt, axis=1)


try:
    os.makedirs("plots/")
except OSError:
    pass

#GRAFICO DE BARRAS DO TEMPO DE EXECUÇÃO PARALELO
trace1 = go.Bar(
    x = df_data.columns,
    y = df_data.loc[list_n[0]],
    error_y=dict(
        type='data',
        array=df_error.loc[list_n[0]],
        visible=True
    ),
    name=str(list_n[0])+' x '+str(list_n[0])
)
trace2 = go.Bar(
    x = df_data.columns,
    y = df_data.loc[list_n[1]],
    error_y=dict(
        type='data',
        array=df_error.loc[list_n[1]],
        visible=True
    ),
    name=str(list_n[1])+' x '+str(list_n[1])
)
trace3 = go.Bar(
    x = df_data.columns,
    y = df_data.loc[list_n[2]],
    error_y=dict(
        type='data',
        array=df_error.loc[list_n[2]],
        visible=True
    ),
    name=str(list_n[2])+' x '+str(list_n[2])
)

data = [trace1, trace2, trace3]

layout = go.Layout(
    title='Tempo de processamento pelo número de processadores e threads',
    xaxis={'title': "Número de processadores 'p' e thread 't' na forma (p, t)", 'type':'category'},
    yaxis={'title': 'Tempo de processamento (min)'},
    barmode='group'
)

fig = go.Figure(data=data, layout=layout)
py.image.save_as(fig, filename='plots/tempo_paralelo-BAR.png')
#py.iplot(fig, filename='error-bar-bar')



# GRÁFICO LINHA DO TEMPO DE EXECUÇÃO SEQUENCIAL
data = [go.Scatter(
    x = [str(n)+' x '+str(n) for n in list_n],
    y = df_data_seq['tempo'],
    mode = 'lines+markers'
)]

layout = go.Layout(
    title='Tempo de processamento sequencial',
    xaxis={'title': "Tamanho da matriz", 'type':'category'},
    yaxis={'title': 'Tempo de processamento (min)'}
)

fig = go.Figure(data=data, layout=layout)
py.image.save_as(fig, filename='plots/tempo_sequencial.png')



# GRÁFICO TEMPO SEQUENCIAL X TEMPO PARALELO
trace1 = go.Bar(
    x = df_data_seq.index,
    y = df_data_seq['tempo'],
    error_y=dict(
        type='data',
        array=df_data_seq['erro'],
        visible=True
    ),
    name='Sequencial'
)
trace2 = go.Bar(
    x = df_media_parallel.index,
    y = df_media_parallel['tempo'],
    error_y=dict(
        type='data',
        array=df_media_parallel['erro'],
        visible=True
    ),
    name='Paralelo'
)

data = [trace1, trace2]

layout = go.Layout(
    title='Média do tempo de processamento',
    xaxis={'title': "Tamanho da matriz", 'type':'category'},
    yaxis={'title': 'Tempo de processamento (min)'},
    barmode='group'
)

fig = go.Figure(data=data, layout=layout)
py.image.save_as(fig, filename='plots/time-seq_paralelo.png')
#py.iplot(fig, filename='error-bar-bar')



line_chart(df_data, 
           "Tempo de processamento paralelo", 
           "Número de processadores 'p' e thread 't' na forma (p, t)", 
           "Tempo de processamento (min)", 
           list_n,
           "plots/tempo_paralelo.png")

line_chart(df_speedup, 
           "Speedup",
           "Número de processadores 'p' e thread 't' na forma (p, t)", 
           "Speedup", 
           list_n,
           "plots/speedup.png")

line_chart(df_eficiencia, 
           "Eficiência",
           "Número de processadores 'p' e thread 't' na forma (p, t)", 
           "Eficiência", 
           list_n,
           "plots/eficiencia.png")


writer = pd.ExcelWriter('estatisticas.xlsx')
df_data.to_excel(writer,'Tempo paralelo')
df_data_seq['tempo'].to_excel(writer,'Tempo sequencial')
df_speedup.to_excel(writer,'Speedup')
df_eficiencia.to_excel(writer,'Eficiência')
writer.save()